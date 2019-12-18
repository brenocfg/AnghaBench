#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct vfio_ccw_private* guest_cp; } ;
struct vfio_ccw_private {TYPE_1__ cp; int /*<<< orphan*/  io_region; int /*<<< orphan*/  cmd_region; } ;
struct TYPE_4__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; int /*<<< orphan*/  cssid; } ;
struct subchannel {TYPE_2__ schid; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_CCW_MSG_EVENT (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vfio_ccw_private*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_ccw_cmd_region ; 
 int /*<<< orphan*/  vfio_ccw_io_region ; 
 int /*<<< orphan*/  vfio_ccw_mdev_unreg (struct subchannel*) ; 
 int /*<<< orphan*/  vfio_ccw_sch_quiesce (struct subchannel*) ; 

__attribute__((used)) static int vfio_ccw_sch_remove(struct subchannel *sch)
{
	struct vfio_ccw_private *private = dev_get_drvdata(&sch->dev);

	vfio_ccw_sch_quiesce(sch);

	vfio_ccw_mdev_unreg(sch);

	dev_set_drvdata(&sch->dev, NULL);

	kmem_cache_free(vfio_ccw_cmd_region, private->cmd_region);
	kmem_cache_free(vfio_ccw_io_region, private->io_region);
	kfree(private->cp.guest_cp);
	kfree(private);

	VFIO_CCW_MSG_EVENT(4, "unbound from subchannel %x.%x.%04x\n",
			   sch->schid.cssid, sch->schid.ssid,
			   sch->schid.sch_no);
	return 0;
}