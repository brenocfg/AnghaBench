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
struct xenvif_queue {int id; TYPE_1__* vif; } ;
struct xenbus_device {char* otherend; } ;
struct backend_info {struct xenbus_device* dev; } ;
struct TYPE_2__ {unsigned int num_queues; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t const strlen (char*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,...) ; 
 int xenbus_gather (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int xenbus_scanf (int /*<<< orphan*/ ,char*,char*,char*,unsigned int*) ; 
 int xenvif_connect_data (struct xenvif_queue*,unsigned long,unsigned long,unsigned int,unsigned int) ; 

__attribute__((used)) static int connect_data_rings(struct backend_info *be,
			      struct xenvif_queue *queue)
{
	struct xenbus_device *dev = be->dev;
	unsigned int num_queues = queue->vif->num_queues;
	unsigned long tx_ring_ref, rx_ring_ref;
	unsigned int tx_evtchn, rx_evtchn;
	int err;
	char *xspath;
	size_t xspathsize;
	const size_t xenstore_path_ext_size = 11; /* sufficient for "/queue-NNN" */

	/* If the frontend requested 1 queue, or we have fallen back
	 * to single queue due to lack of frontend support for multi-
	 * queue, expect the remaining XenStore keys in the toplevel
	 * directory. Otherwise, expect them in a subdirectory called
	 * queue-N.
	 */
	if (num_queues == 1) {
		xspath = kzalloc(strlen(dev->otherend) + 1, GFP_KERNEL);
		if (!xspath) {
			xenbus_dev_fatal(dev, -ENOMEM,
					 "reading ring references");
			return -ENOMEM;
		}
		strcpy(xspath, dev->otherend);
	} else {
		xspathsize = strlen(dev->otherend) + xenstore_path_ext_size;
		xspath = kzalloc(xspathsize, GFP_KERNEL);
		if (!xspath) {
			xenbus_dev_fatal(dev, -ENOMEM,
					 "reading ring references");
			return -ENOMEM;
		}
		snprintf(xspath, xspathsize, "%s/queue-%u", dev->otherend,
			 queue->id);
	}

	err = xenbus_gather(XBT_NIL, xspath,
			    "tx-ring-ref", "%lu", &tx_ring_ref,
			    "rx-ring-ref", "%lu", &rx_ring_ref, NULL);
	if (err) {
		xenbus_dev_fatal(dev, err,
				 "reading %s/ring-ref",
				 xspath);
		goto err;
	}

	/* Try split event channels first, then single event channel. */
	err = xenbus_gather(XBT_NIL, xspath,
			    "event-channel-tx", "%u", &tx_evtchn,
			    "event-channel-rx", "%u", &rx_evtchn, NULL);
	if (err < 0) {
		err = xenbus_scanf(XBT_NIL, xspath,
				   "event-channel", "%u", &tx_evtchn);
		if (err < 0) {
			xenbus_dev_fatal(dev, err,
					 "reading %s/event-channel(-tx/rx)",
					 xspath);
			goto err;
		}
		rx_evtchn = tx_evtchn;
	}

	/* Map the shared frame, irq etc. */
	err = xenvif_connect_data(queue, tx_ring_ref, rx_ring_ref,
				  tx_evtchn, rx_evtchn);
	if (err) {
		xenbus_dev_fatal(dev, err,
				 "mapping shared-frames %lu/%lu port tx %u rx %u",
				 tx_ring_ref, rx_ring_ref,
				 tx_evtchn, rx_evtchn);
		goto err;
	}

	err = 0;
err: /* Regular return falls through with err == 0 */
	kfree(xspath);
	return err;
}