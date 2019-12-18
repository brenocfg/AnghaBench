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
struct ptp_qoriq {int dummy; } ;
struct device {int dummy; } ;
struct fsl_mc_device {int /*<<< orphan*/  mc_io; int /*<<< orphan*/  mc_handle; struct device dev; } ;

/* Variables and functions */
 struct ptp_qoriq* dev_get_drvdata (struct device*) ; 
 int dpaa2_phc_index ; 
 int /*<<< orphan*/  dprtc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_mc_free_irqs (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  fsl_mc_portal_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_qoriq_free (struct ptp_qoriq*) ; 

__attribute__((used)) static int dpaa2_ptp_remove(struct fsl_mc_device *mc_dev)
{
	struct device *dev = &mc_dev->dev;
	struct ptp_qoriq *ptp_qoriq;

	ptp_qoriq = dev_get_drvdata(dev);

	dpaa2_phc_index = -1;
	ptp_qoriq_free(ptp_qoriq);

	fsl_mc_free_irqs(mc_dev);
	dprtc_close(mc_dev->mc_io, 0, mc_dev->mc_handle);
	fsl_mc_portal_free(mc_dev->mc_io);

	return 0;
}