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
typedef  int /*<<< orphan*/  u32 ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct hl_debug_params {int op; } ;

/* Variables and functions */
 int EINVAL ; 
#define  HL_DEBUG_OP_BMON 134 
#define  HL_DEBUG_OP_ETF 133 
#define  HL_DEBUG_OP_ETR 132 
#define  HL_DEBUG_OP_FUNNEL 131 
#define  HL_DEBUG_OP_SPMU 130 
#define  HL_DEBUG_OP_STM 129 
#define  HL_DEBUG_OP_TIMESTAMP 128 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int goya_config_bmon (struct hl_device*,struct hl_debug_params*) ; 
 int goya_config_etf (struct hl_device*,struct hl_debug_params*) ; 
 int goya_config_etr (struct hl_device*,struct hl_debug_params*) ; 
 int goya_config_funnel (struct hl_device*,struct hl_debug_params*) ; 
 int goya_config_spmu (struct hl_device*,struct hl_debug_params*) ; 
 int goya_config_stm (struct hl_device*,struct hl_debug_params*) ; 
 int /*<<< orphan*/  mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG ; 

int goya_debug_coresight(struct hl_device *hdev, void *data)
{
	struct hl_debug_params *params = data;
	u32 val;
	int rc = 0;

	switch (params->op) {
	case HL_DEBUG_OP_STM:
		rc = goya_config_stm(hdev, params);
		break;
	case HL_DEBUG_OP_ETF:
		rc = goya_config_etf(hdev, params);
		break;
	case HL_DEBUG_OP_ETR:
		rc = goya_config_etr(hdev, params);
		break;
	case HL_DEBUG_OP_FUNNEL:
		rc = goya_config_funnel(hdev, params);
		break;
	case HL_DEBUG_OP_BMON:
		rc = goya_config_bmon(hdev, params);
		break;
	case HL_DEBUG_OP_SPMU:
		rc = goya_config_spmu(hdev, params);
		break;
	case HL_DEBUG_OP_TIMESTAMP:
		/* Do nothing as this opcode is deprecated */
		break;

	default:
		dev_err(hdev->dev, "Unknown coresight id %d\n", params->op);
		return -EINVAL;
	}

	/* Perform read from the device to flush all configuration */
	val = RREG32(mmPCIE_DBI_DEVICE_ID_VENDOR_ID_REG);

	return rc;
}