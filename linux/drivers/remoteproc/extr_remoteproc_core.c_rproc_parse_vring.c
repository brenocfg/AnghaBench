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
struct rproc_vring {struct rproc_vdev* rvdev; scalar_t__ align; scalar_t__ len; } ;
struct rproc_vdev {struct rproc_vring* vring; struct rproc* rproc; } ;
struct device {int dummy; } ;
struct rproc {struct device dev; } ;
struct fw_rsc_vdev_vring {scalar_t__ align; scalar_t__ num; int /*<<< orphan*/  da; } ;
struct fw_rsc_vdev {struct fw_rsc_vdev_vring* vring; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
rproc_parse_vring(struct rproc_vdev *rvdev, struct fw_rsc_vdev *rsc, int i)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rproc->dev;
	struct fw_rsc_vdev_vring *vring = &rsc->vring[i];
	struct rproc_vring *rvring = &rvdev->vring[i];

	dev_dbg(dev, "vdev rsc: vring%d: da 0x%x, qsz %d, align %d\n",
		i, vring->da, vring->num, vring->align);

	/* verify queue size and vring alignment are sane */
	if (!vring->num || !vring->align) {
		dev_err(dev, "invalid qsz (%d) or alignment (%d)\n",
			vring->num, vring->align);
		return -EINVAL;
	}

	rvring->len = vring->num;
	rvring->align = vring->align;
	rvring->rvdev = rvdev;

	return 0;
}