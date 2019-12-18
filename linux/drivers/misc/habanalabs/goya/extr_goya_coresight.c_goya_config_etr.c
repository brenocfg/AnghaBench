#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_debug_params_etr {int buffer_size; int sink_mode; int /*<<< orphan*/  buffer_address; } ;
struct hl_debug_params {int output_size; scalar_t__ output; struct hl_debug_params_etr* input; scalar_t__ enable; } ;

/* Variables and functions */
 int CFG_BASE ; 
 int CORESIGHT_UNLOCK ; 
 int EINVAL ; 
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int goya_coresight_timeout (struct hl_device*,int,int,int) ; 
 int /*<<< orphan*/  goya_etr_validate_address (struct hl_device*,int /*<<< orphan*/ ,int) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int mmPSOC_ETR_BASE ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goya_config_etr(struct hl_device *hdev,
		struct hl_debug_params *params)
{
	struct hl_debug_params_etr *input;
	u64 base_reg = mmPSOC_ETR_BASE - CFG_BASE;
	u32 val;
	int rc;

	WREG32(base_reg + 0xFB0, CORESIGHT_UNLOCK);

	val = RREG32(base_reg + 0x304);
	val |= 0x1000;
	WREG32(base_reg + 0x304, val);
	val |= 0x40;
	WREG32(base_reg + 0x304, val);

	rc = goya_coresight_timeout(hdev, base_reg + 0x304, 6, false);
	if (rc) {
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		return rc;
	}

	rc = goya_coresight_timeout(hdev, base_reg + 0xC, 2, true);
	if (rc) {
		dev_err(hdev->dev, "Failed to %s ETR on timeout, error %d\n",
				params->enable ? "enable" : "disable", rc);
		return rc;
	}

	WREG32(base_reg + 0x20, 0);

	if (params->enable) {
		input = params->input;

		if (!input)
			return -EINVAL;

		if (input->buffer_size == 0) {
			dev_err(hdev->dev,
				"ETR buffer size should be bigger than 0\n");
			return -EINVAL;
		}

		if (!goya_etr_validate_address(hdev,
				input->buffer_address, input->buffer_size)) {
			dev_err(hdev->dev, "buffer address is not valid\n");
			return -EINVAL;
		}

		WREG32(base_reg + 0x34, 0x3FFC);
		WREG32(base_reg + 0x4, input->buffer_size);
		WREG32(base_reg + 0x28, input->sink_mode);
		WREG32(base_reg + 0x110, 0x700);
		WREG32(base_reg + 0x118,
				lower_32_bits(input->buffer_address));
		WREG32(base_reg + 0x11C,
				upper_32_bits(input->buffer_address));
		WREG32(base_reg + 0x304, 3);
		WREG32(base_reg + 0x308, 0xA);
		WREG32(base_reg + 0x20, 1);
	} else {
		WREG32(base_reg + 0x34, 0);
		WREG32(base_reg + 0x4, 0x400);
		WREG32(base_reg + 0x118, 0);
		WREG32(base_reg + 0x11C, 0);
		WREG32(base_reg + 0x308, 0);
		WREG32(base_reg + 0x28, 0);
		WREG32(base_reg + 0x304, 0);

		if (params->output_size >= sizeof(u64)) {
			u32 rwp, rwphi;

			/*
			 * The trace buffer address is 40 bits wide. The end of
			 * the buffer is set in the RWP register (lower 32
			 * bits), and in the RWPHI register (upper 8 bits).
			 */
			rwp = RREG32(base_reg + 0x18);
			rwphi = RREG32(base_reg + 0x3c) & 0xff;
			*(u64 *) params->output = ((u64) rwphi << 32) | rwp;
		}
	}

	return 0;
}