#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xenvif {struct backend_info* be; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct xenbus_device {TYPE_1__ dev; int /*<<< orphan*/  otherend_id; int /*<<< orphan*/  nodename; } ;
struct backend_info {struct xenvif* vif; struct xenbus_device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct xenvif*) ; 
 int /*<<< orphan*/  KOBJ_ONLINE ; 
 int PTR_ERR (struct xenvif*) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,long*) ; 
 struct xenvif* xenvif_alloc (TYPE_1__*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static int backend_create_xenvif(struct backend_info *be)
{
	int err;
	long handle;
	struct xenbus_device *dev = be->dev;
	struct xenvif *vif;

	if (be->vif != NULL)
		return 0;

	err = xenbus_scanf(XBT_NIL, dev->nodename, "handle", "%li", &handle);
	if (err != 1) {
		xenbus_dev_fatal(dev, err, "reading handle");
		return (err < 0) ? err : -EINVAL;
	}

	vif = xenvif_alloc(&dev->dev, dev->otherend_id, handle);
	if (IS_ERR(vif)) {
		err = PTR_ERR(vif);
		xenbus_dev_fatal(dev, err, "creating interface");
		return err;
	}
	be->vif = vif;
	vif->be = be;

	kobject_uevent(&dev->dev.kobj, KOBJ_ONLINE);
	return 0;
}