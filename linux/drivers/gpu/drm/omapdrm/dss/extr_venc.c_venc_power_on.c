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
typedef  int u32 ;
struct venc_device {scalar_t__ type; int invert_polarity; int /*<<< orphan*/  dss; int /*<<< orphan*/  vdda_dac_reg; int /*<<< orphan*/  output; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 scalar_t__ OMAP_DSS_VENC_TYPE_COMPOSITE ; 
 int /*<<< orphan*/  VENC_OUTPUT_CONTROL ; 
 int dss_mgr_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_set_dac_pwrdn_bgz (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dss_set_venc_output (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_reset (struct venc_device*) ; 
 int venc_runtime_get (struct venc_device*) ; 
 int /*<<< orphan*/  venc_runtime_put (struct venc_device*) ; 
 int /*<<< orphan*/  venc_write_config (struct venc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  venc_write_reg (struct venc_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int venc_power_on(struct venc_device *venc)
{
	u32 l;
	int r;

	r = venc_runtime_get(venc);
	if (r)
		goto err0;

	venc_reset(venc);
	venc_write_config(venc, venc->config);

	dss_set_venc_output(venc->dss, venc->type);
	dss_set_dac_pwrdn_bgz(venc->dss, 1);

	l = 0;

	if (venc->type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l |= 1 << 1;
	else /* S-Video */
		l |= (1 << 0) | (1 << 2);

	if (venc->invert_polarity == false)
		l |= 1 << 3;

	venc_write_reg(venc, VENC_OUTPUT_CONTROL, l);

	r = regulator_enable(venc->vdda_dac_reg);
	if (r)
		goto err1;

	r = dss_mgr_enable(&venc->output);
	if (r)
		goto err2;

	return 0;

err2:
	regulator_disable(venc->vdda_dac_reg);
err1:
	venc_write_reg(venc, VENC_OUTPUT_CONTROL, 0);
	dss_set_dac_pwrdn_bgz(venc->dss, 0);

	venc_runtime_put(venc);
err0:
	return r;
}