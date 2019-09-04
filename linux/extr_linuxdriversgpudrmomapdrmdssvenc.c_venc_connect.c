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
struct venc_device {int /*<<< orphan*/  output; } ;
struct omap_dss_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*,int /*<<< orphan*/ ) ; 
 int dss_mgr_connect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 int /*<<< orphan*/  dss_mgr_disconnect (int /*<<< orphan*/ *,struct omap_dss_device*) ; 
 struct venc_device* dssdev_to_venc (struct omap_dss_device*) ; 
 int omapdss_output_set_device (struct omap_dss_device*,struct omap_dss_device*) ; 
 int venc_init_regulator (struct venc_device*) ; 

__attribute__((used)) static int venc_connect(struct omap_dss_device *dssdev,
		struct omap_dss_device *dst)
{
	struct venc_device *venc = dssdev_to_venc(dssdev);
	int r;

	r = venc_init_regulator(venc);
	if (r)
		return r;

	r = dss_mgr_connect(&venc->output, dssdev);
	if (r)
		return r;

	r = omapdss_output_set_device(dssdev, dst);
	if (r) {
		DSSERR("failed to connect output to new device: %s\n",
				dst->name);
		dss_mgr_disconnect(&venc->output, dssdev);
		return r;
	}

	return 0;
}