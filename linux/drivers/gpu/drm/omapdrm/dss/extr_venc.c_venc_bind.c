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
typedef  scalar_t__ u8 ;
struct venc_device {int /*<<< orphan*/  debugfs; struct dss_device* dss; } ;
struct dss_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENC_REV_ID ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 
 struct venc_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dss_debugfs_create_file (struct dss_device*,char*,int /*<<< orphan*/ ,struct venc_device*) ; 
 struct dss_device* dss_get_device (struct device*) ; 
 int /*<<< orphan*/  venc_dump_regs ; 
 int venc_read_reg (struct venc_device*,int /*<<< orphan*/ ) ; 
 int venc_runtime_get (struct venc_device*) ; 
 int /*<<< orphan*/  venc_runtime_put (struct venc_device*) ; 

__attribute__((used)) static int venc_bind(struct device *dev, struct device *master, void *data)
{
	struct dss_device *dss = dss_get_device(master);
	struct venc_device *venc = dev_get_drvdata(dev);
	u8 rev_id;
	int r;

	venc->dss = dss;

	r = venc_runtime_get(venc);
	if (r)
		return r;

	rev_id = (u8)(venc_read_reg(venc, VENC_REV_ID) & 0xff);
	dev_dbg(dev, "OMAP VENC rev %d\n", rev_id);

	venc_runtime_put(venc);

	venc->debugfs = dss_debugfs_create_file(dss, "venc", venc_dump_regs,
						venc);

	return 0;
}