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
struct device {struct device* parent; int /*<<< orphan*/ * bus; } ;
struct TYPE_3__ {struct device device; } ;
struct ap_queue {scalar_t__ state; TYPE_1__ ap_dev; struct ap_card* card; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct device device; } ;
struct ap_card {int raw_hwtype; unsigned int functions; TYPE_2__ ap_dev; } ;
typedef  scalar_t__ ap_qid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DBF (int /*<<< orphan*/ ,char*,int,...) ; 
 int AP_DOMAINS ; 
 scalar_t__ AP_MKQID (int,int) ; 
 scalar_t__ AP_STATE_BORKED ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int ENODEV ; 
 int /*<<< orphan*/  __ap_queue_devices_with_id_unregister ; 
 int /*<<< orphan*/  __match_card_device_with_id ; 
 int /*<<< orphan*/  __match_queue_device_with_qid ; 
 int /*<<< orphan*/  ap_bus_type ; 
 struct ap_card* ap_card_create (int,int,int,int,unsigned int) ; 
 int ap_get_compatible_type (scalar_t__,int,unsigned int) ; 
 int ap_query_queue (scalar_t__,int*,int*,unsigned int*) ; 
 struct ap_queue* ap_queue_create (scalar_t__,int) ; 
 struct device* ap_root_device ; 
 int /*<<< orphan*/  ap_test_config_card_id (int) ; 
 int /*<<< orphan*/  ap_test_config_usage_domain (int) ; 
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int,...) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_card* to_ap_card (struct device*) ; 
 struct ap_queue* to_ap_queue (struct device*) ; 

__attribute__((used)) static void _ap_scan_bus_adapter(int id)
{
	ap_qid_t qid;
	unsigned int func;
	struct ap_card *ac;
	struct device *dev;
	struct ap_queue *aq;
	int rc, dom, depth, type, comp_type, borked;

	/* check if there is a card device registered with this id */
	dev = bus_find_device(&ap_bus_type, NULL,
			      (void *)(long) id,
			      __match_card_device_with_id);
	ac = dev ? to_ap_card(dev) : NULL;
	if (!ap_test_config_card_id(id)) {
		if (dev) {
			/* Card device has been removed from configuration */
			bus_for_each_dev(&ap_bus_type, NULL,
					 (void *)(long) id,
					 __ap_queue_devices_with_id_unregister);
			device_unregister(dev);
			put_device(dev);
		}
		return;
	}

	/*
	 * This card id is enabled in the configuration. If we already have
	 * a card device with this id, check if type and functions are still
	 * the very same. Also verify that at least one queue is available.
	 */
	if (ac) {
		/* find the first valid queue */
		for (dom = 0; dom < AP_DOMAINS; dom++) {
			qid = AP_MKQID(id, dom);
			if (ap_query_queue(qid, &depth, &type, &func) == 0)
				break;
		}
		borked = 0;
		if (dom >= AP_DOMAINS) {
			/* no accessible queue on this card */
			borked = 1;
		} else if (ac->raw_hwtype != type) {
			/* card type has changed */
			AP_DBF(DBF_INFO, "card=%02x type changed.\n", id);
			borked = 1;
		} else if (ac->functions != func) {
			/* card functions have changed */
			AP_DBF(DBF_INFO, "card=%02x functions changed.\n", id);
			borked = 1;
		}
		if (borked) {
			/* unregister card device and associated queues */
			bus_for_each_dev(&ap_bus_type, NULL,
					 (void *)(long) id,
					 __ap_queue_devices_with_id_unregister);
			device_unregister(dev);
			put_device(dev);
			/* go back if there is no valid queue on this card */
			if (dom >= AP_DOMAINS)
				return;
			ac = NULL;
		}
	}

	/*
	 * Go through all possible queue ids. Check and maybe create or release
	 * queue devices for this card. If there exists no card device yet,
	 * create a card device also.
	 */
	for (dom = 0; dom < AP_DOMAINS; dom++) {
		qid = AP_MKQID(id, dom);
		dev = bus_find_device(&ap_bus_type, NULL,
				      (void *)(long) qid,
				      __match_queue_device_with_qid);
		aq = dev ? to_ap_queue(dev) : NULL;
		if (!ap_test_config_usage_domain(dom)) {
			if (dev) {
				/* Queue device exists but has been
				 * removed from configuration.
				 */
				device_unregister(dev);
				put_device(dev);
			}
			continue;
		}
		/* try to fetch infos about this queue */
		rc = ap_query_queue(qid, &depth, &type, &func);
		if (dev) {
			if (rc == -ENODEV)
				borked = 1;
			else {
				spin_lock_bh(&aq->lock);
				borked = aq->state == AP_STATE_BORKED;
				spin_unlock_bh(&aq->lock);
			}
			if (borked) {
				/* Remove broken device */
				AP_DBF(DBF_DEBUG,
				       "removing broken queue=%02x.%04x\n",
				       id, dom);
				device_unregister(dev);
			}
			put_device(dev);
			continue;
		}
		if (rc)
			continue;
		/* a new queue device is needed, check out comp type */
		comp_type = ap_get_compatible_type(qid, type, func);
		if (!comp_type)
			continue;
		/* maybe a card device needs to be created first */
		if (!ac) {
			ac = ap_card_create(id, depth, type, comp_type, func);
			if (!ac)
				continue;
			ac->ap_dev.device.bus = &ap_bus_type;
			ac->ap_dev.device.parent = ap_root_device;
			dev_set_name(&ac->ap_dev.device, "card%02x", id);
			/* Register card device with AP bus */
			rc = device_register(&ac->ap_dev.device);
			if (rc) {
				put_device(&ac->ap_dev.device);
				ac = NULL;
				break;
			}
			/* get it and thus adjust reference counter */
			get_device(&ac->ap_dev.device);
		}
		/* now create the new queue device */
		aq = ap_queue_create(qid, comp_type);
		if (!aq)
			continue;
		aq->card = ac;
		aq->ap_dev.device.bus = &ap_bus_type;
		aq->ap_dev.device.parent = &ac->ap_dev.device;
		dev_set_name(&aq->ap_dev.device, "%02x.%04x", id, dom);
		/* Register queue device */
		rc = device_register(&aq->ap_dev.device);
		if (rc) {
			put_device(&aq->ap_dev.device);
			continue;
		}
	} /* end domain loop */

	if (ac)
		put_device(&ac->ap_dev.device);
}