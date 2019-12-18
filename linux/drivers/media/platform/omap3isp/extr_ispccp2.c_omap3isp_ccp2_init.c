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
struct isp_ccp2_device {int /*<<< orphan*/ * phy; int /*<<< orphan*/ * vdds_csib; int /*<<< orphan*/  wait; } ;
struct isp_device {scalar_t__ revision; int /*<<< orphan*/  isp_csiphy1; int /*<<< orphan*/  isp_csiphy2; int /*<<< orphan*/  dev; struct isp_ccp2_device isp_ccp2; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ ISP_REVISION_15_0 ; 
 scalar_t__ ISP_REVISION_2_0 ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int ccp2_init_entities (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  ccp2_reset (struct isp_ccp2_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

int omap3isp_ccp2_init(struct isp_device *isp)
{
	struct isp_ccp2_device *ccp2 = &isp->isp_ccp2;
	int ret;

	init_waitqueue_head(&ccp2->wait);

	/*
	 * On the OMAP34xx the CSI1 receiver is operated in the CSIb IO
	 * complex, which is powered by vdds_csib power rail. Hence the
	 * request for the regulator.
	 *
	 * On the OMAP36xx, the CCP2 uses the CSI PHY1 or PHY2, shared with
	 * the CSI2c or CSI2a receivers. The PHY then needs to be explicitly
	 * configured.
	 *
	 * TODO: Don't hardcode the usage of PHY1 (shared with CSI2c).
	 */
	if (isp->revision == ISP_REVISION_2_0) {
		ccp2->vdds_csib = devm_regulator_get(isp->dev, "vdds_csib");
		if (IS_ERR(ccp2->vdds_csib)) {
			if (PTR_ERR(ccp2->vdds_csib) == -EPROBE_DEFER) {
				dev_dbg(isp->dev,
					"Can't get regulator vdds_csib, deferring probing\n");
				return -EPROBE_DEFER;
			}
			dev_dbg(isp->dev,
				"Could not get regulator vdds_csib\n");
			ccp2->vdds_csib = NULL;
		}
		ccp2->phy = &isp->isp_csiphy2;
	} else if (isp->revision == ISP_REVISION_15_0) {
		ccp2->phy = &isp->isp_csiphy1;
	}

	ret = ccp2_init_entities(ccp2);
	if (ret < 0)
		return ret;

	ccp2_reset(ccp2);
	return 0;
}