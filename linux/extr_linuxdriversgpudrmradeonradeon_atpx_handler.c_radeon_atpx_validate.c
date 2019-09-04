#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  int u32 ;
typedef  size_t u16 ;
struct TYPE_5__ {int i2c_mux_cntl; int disp_mux_cntl; int power_cntl; scalar_t__ px_params; } ;
struct radeon_atpx {int is_hybrid; TYPE_2__ functions; int /*<<< orphan*/  handle; } ;
struct atpx_px_params {int flags; int valid_flags; } ;
typedef  int /*<<< orphan*/  output ;
struct TYPE_6__ {int /*<<< orphan*/  bridge_pm_usable; } ;

/* Variables and functions */
 int ATPX_CRT1_RGB_SIGNAL_MUXED ; 
 int ATPX_DFP_SIGNAL_MUXED ; 
 int ATPX_DYNAMIC_DGPU_POWER_OFF_SUPPORTED ; 
 int ATPX_DYNAMIC_PX_SUPPORTED ; 
 int /*<<< orphan*/  ATPX_FUNCTION_GET_PX_PARAMETERS ; 
 int ATPX_MS_HYBRID_GFX_SUPPORTED ; 
 int ATPX_SEPARATE_MUX_FOR_I2C ; 
 int ATPX_TV_SIGNAL_MUXED ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atpx_px_params*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atpx_px_params*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 union acpi_object* radeon_atpx_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ radeon_atpx_priv ; 

__attribute__((used)) static int radeon_atpx_validate(struct radeon_atpx *atpx)
{
	u32 valid_bits = 0;

	if (atpx->functions.px_params) {
		union acpi_object *info;
		struct atpx_px_params output;
		size_t size;

		info = radeon_atpx_call(atpx->handle, ATPX_FUNCTION_GET_PX_PARAMETERS, NULL);
		if (!info)
			return -EIO;

		memset(&output, 0, sizeof(output));

		size = *(u16 *) info->buffer.pointer;
		if (size < 10) {
			printk("ATPX buffer is too small: %zu\n", size);
			kfree(info);
			return -EINVAL;
		}
		size = min(sizeof(output), size);

		memcpy(&output, info->buffer.pointer, size);

		valid_bits = output.flags & output.valid_flags;

		kfree(info);
	}

	/* if separate mux flag is set, mux controls are required */
	if (valid_bits & ATPX_SEPARATE_MUX_FOR_I2C) {
		atpx->functions.i2c_mux_cntl = true;
		atpx->functions.disp_mux_cntl = true;
	}
	/* if any outputs are muxed, mux controls are required */
	if (valid_bits & (ATPX_CRT1_RGB_SIGNAL_MUXED |
			  ATPX_TV_SIGNAL_MUXED |
			  ATPX_DFP_SIGNAL_MUXED))
		atpx->functions.disp_mux_cntl = true;

	/* some bioses set these bits rather than flagging power_cntl as supported */
	if (valid_bits & (ATPX_DYNAMIC_PX_SUPPORTED |
			  ATPX_DYNAMIC_DGPU_POWER_OFF_SUPPORTED))
		atpx->functions.power_cntl = true;

	atpx->is_hybrid = false;
	if (valid_bits & ATPX_MS_HYBRID_GFX_SUPPORTED) {
		printk("ATPX Hybrid Graphics\n");
		/*
		 * Disable legacy PM methods only when pcie port PM is usable,
		 * otherwise the device might fail to power off or power on.
		 */
		atpx->functions.power_cntl = !radeon_atpx_priv.bridge_pm_usable;
		atpx->is_hybrid = true;
	}

	return 0;
}