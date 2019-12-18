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
struct venc_device {int /*<<< orphan*/  vdda_dac_reg; int /*<<< orphan*/  output; int /*<<< orphan*/  dss; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENC_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  dss_mgr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_set_dac_pwrdn_bgz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_runtime_put (struct venc_device*) ; 
 int /*<<< orphan*/  venc_write_reg (struct venc_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venc_power_off(struct venc_device *venc)
{
	venc_write_reg(venc, VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(venc->dss, 0);

	dss_mgr_disable(&venc->output);

	regulator_disable(venc->vdda_dac_reg);

	venc_runtime_put(venc);
}