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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  nodename; int /*<<< orphan*/  dev; } ;
struct backend_info {char const* hotplug_script; int /*<<< orphan*/  state; struct xenbus_device* dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char const*) ; 
 int PTR_ERR (char const*) ; 
 struct xenbus_transaction XBT_NIL ; 
 int /*<<< orphan*/  XenbusStateInitialising ; 
 int backend_create_xenvif (struct backend_info*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct backend_info*) ; 
 struct backend_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netback_remove (struct xenbus_device*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int separate_tx_rx_irq ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,...) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,int) ; 
 char* xenbus_read (struct xenbus_transaction,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 
 int xenvif_max_queues ; 

__attribute__((used)) static int netback_probe(struct xenbus_device *dev,
			 const struct xenbus_device_id *id)
{
	const char *message;
	struct xenbus_transaction xbt;
	int err;
	int sg;
	const char *script;
	struct backend_info *be = kzalloc(sizeof(struct backend_info),
					  GFP_KERNEL);
	if (!be) {
		xenbus_dev_fatal(dev, -ENOMEM,
				 "allocating backend structure");
		return -ENOMEM;
	}

	be->dev = dev;
	dev_set_drvdata(&dev->dev, be);

	be->state = XenbusStateInitialising;
	err = xenbus_switch_state(dev, XenbusStateInitialising);
	if (err)
		goto fail;

	sg = 1;

	do {
		err = xenbus_transaction_start(&xbt);
		if (err) {
			xenbus_dev_fatal(dev, err, "starting transaction");
			goto fail;
		}

		err = xenbus_printf(xbt, dev->nodename, "feature-sg", "%d", sg);
		if (err) {
			message = "writing feature-sg";
			goto abort_transaction;
		}

		err = xenbus_printf(xbt, dev->nodename, "feature-gso-tcpv4",
				    "%d", sg);
		if (err) {
			message = "writing feature-gso-tcpv4";
			goto abort_transaction;
		}

		err = xenbus_printf(xbt, dev->nodename, "feature-gso-tcpv6",
				    "%d", sg);
		if (err) {
			message = "writing feature-gso-tcpv6";
			goto abort_transaction;
		}

		/* We support partial checksum setup for IPv6 packets */
		err = xenbus_printf(xbt, dev->nodename,
				    "feature-ipv6-csum-offload",
				    "%d", 1);
		if (err) {
			message = "writing feature-ipv6-csum-offload";
			goto abort_transaction;
		}

		/* We support rx-copy path. */
		err = xenbus_printf(xbt, dev->nodename,
				    "feature-rx-copy", "%d", 1);
		if (err) {
			message = "writing feature-rx-copy";
			goto abort_transaction;
		}

		/*
		 * We don't support rx-flip path (except old guests who don't
		 * grok this feature flag).
		 */
		err = xenbus_printf(xbt, dev->nodename,
				    "feature-rx-flip", "%d", 0);
		if (err) {
			message = "writing feature-rx-flip";
			goto abort_transaction;
		}

		/* We support dynamic multicast-control. */
		err = xenbus_printf(xbt, dev->nodename,
				    "feature-multicast-control", "%d", 1);
		if (err) {
			message = "writing feature-multicast-control";
			goto abort_transaction;
		}

		err = xenbus_printf(xbt, dev->nodename,
				    "feature-dynamic-multicast-control",
				    "%d", 1);
		if (err) {
			message = "writing feature-dynamic-multicast-control";
			goto abort_transaction;
		}

		err = xenbus_transaction_end(xbt, 0);
	} while (err == -EAGAIN);

	if (err) {
		xenbus_dev_fatal(dev, err, "completing transaction");
		goto fail;
	}

	/*
	 * Split event channels support, this is optional so it is not
	 * put inside the above loop.
	 */
	err = xenbus_printf(XBT_NIL, dev->nodename,
			    "feature-split-event-channels",
			    "%u", separate_tx_rx_irq);
	if (err)
		pr_debug("Error writing feature-split-event-channels\n");

	/* Multi-queue support: This is an optional feature. */
	err = xenbus_printf(XBT_NIL, dev->nodename,
			    "multi-queue-max-queues", "%u", xenvif_max_queues);
	if (err)
		pr_debug("Error writing multi-queue-max-queues\n");

	err = xenbus_printf(XBT_NIL, dev->nodename,
			    "feature-ctrl-ring",
			    "%u", true);
	if (err)
		pr_debug("Error writing feature-ctrl-ring\n");

	script = xenbus_read(XBT_NIL, dev->nodename, "script", NULL);
	if (IS_ERR(script)) {
		err = PTR_ERR(script);
		xenbus_dev_fatal(dev, err, "reading script");
		goto fail;
	}

	be->hotplug_script = script;


	/* This kicks hotplug scripts, so do it immediately. */
	err = backend_create_xenvif(be);
	if (err)
		goto fail;

	return 0;

abort_transaction:
	xenbus_transaction_end(xbt, 1);
	xenbus_dev_fatal(dev, err, "%s", message);
fail:
	pr_debug("failed\n");
	netback_remove(dev);
	return err;
}