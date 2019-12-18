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
struct xenbus_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  otherend_id; int /*<<< orphan*/  otherend; } ;
struct pvcalls_fedata {int irq; int /*<<< orphan*/ * sring; int /*<<< orphan*/  list; int /*<<< orphan*/  socket_lock; int /*<<< orphan*/  socketpass_mappings; int /*<<< orphan*/  socket_mappings; struct xenbus_device* dev; int /*<<< orphan*/  ring; } ;
typedef  int grant_ref_t ;
struct TYPE_2__ {int /*<<< orphan*/  frontends_lock; int /*<<< orphan*/  frontends; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACK_RING_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int XEN_PAGE_SIZE ; 
 int bind_interdomain_evtchn_to_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct pvcalls_fedata*) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pvcalls_fedata*) ; 
 struct pvcalls_fedata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pvcalls_back_event ; 
 TYPE_1__ pvcalls_back_global ; 
 int request_threaded_irq (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct xenbus_device*) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenbus_device*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,int /*<<< orphan*/ ) ; 
 int xenbus_map_ring_valloc (struct xenbus_device*,int*,int,void**) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int*) ; 
 int /*<<< orphan*/  xenbus_unmap_ring_vfree (struct xenbus_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int backend_connect(struct xenbus_device *dev)
{
	int err, evtchn;
	grant_ref_t ring_ref;
	struct pvcalls_fedata *fedata = NULL;

	fedata = kzalloc(sizeof(struct pvcalls_fedata), GFP_KERNEL);
	if (!fedata)
		return -ENOMEM;

	fedata->irq = -1;
	err = xenbus_scanf(XBT_NIL, dev->otherend, "port", "%u",
			   &evtchn);
	if (err != 1) {
		err = -EINVAL;
		xenbus_dev_fatal(dev, err, "reading %s/event-channel",
				 dev->otherend);
		goto error;
	}

	err = xenbus_scanf(XBT_NIL, dev->otherend, "ring-ref", "%u", &ring_ref);
	if (err != 1) {
		err = -EINVAL;
		xenbus_dev_fatal(dev, err, "reading %s/ring-ref",
				 dev->otherend);
		goto error;
	}

	err = bind_interdomain_evtchn_to_irq(dev->otherend_id, evtchn);
	if (err < 0)
		goto error;
	fedata->irq = err;

	err = request_threaded_irq(fedata->irq, NULL, pvcalls_back_event,
				   IRQF_ONESHOT, "pvcalls-back", dev);
	if (err < 0)
		goto error;

	err = xenbus_map_ring_valloc(dev, &ring_ref, 1,
				     (void **)&fedata->sring);
	if (err < 0)
		goto error;

	BACK_RING_INIT(&fedata->ring, fedata->sring, XEN_PAGE_SIZE * 1);
	fedata->dev = dev;

	INIT_LIST_HEAD(&fedata->socket_mappings);
	INIT_RADIX_TREE(&fedata->socketpass_mappings, GFP_KERNEL);
	sema_init(&fedata->socket_lock, 1);
	dev_set_drvdata(&dev->dev, fedata);

	down(&pvcalls_back_global.frontends_lock);
	list_add_tail(&fedata->list, &pvcalls_back_global.frontends);
	up(&pvcalls_back_global.frontends_lock);

	return 0;

 error:
	if (fedata->irq >= 0)
		unbind_from_irqhandler(fedata->irq, dev);
	if (fedata->sring != NULL)
		xenbus_unmap_ring_vfree(dev, fedata->sring);
	kfree(fedata);
	return err;
}