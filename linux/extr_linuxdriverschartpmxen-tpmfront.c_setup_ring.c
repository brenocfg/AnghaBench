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
struct xenbus_device {int /*<<< orphan*/  nodename; } ;
struct tpm_private {int irq; int /*<<< orphan*/  evtchn; int /*<<< orphan*/  ring_ref; void* shr; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  XenbusStateInitialised ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_page (int) ; 
 int bind_evtchn_to_irqhandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tpm_private*) ; 
 int /*<<< orphan*/  tpmif_interrupt ; 
 int xenbus_alloc_evtchn (struct xenbus_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_error (struct xenbus_device*,int,char*,char const*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_grant_ring (struct xenbus_device*,void*,int,int /*<<< orphan*/ *) ; 
 int xenbus_printf (struct xenbus_transaction,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  xenbus_switch_state (struct xenbus_device*,int /*<<< orphan*/ ) ; 
 int xenbus_transaction_end (struct xenbus_transaction,int) ; 
 int xenbus_transaction_start (struct xenbus_transaction*) ; 

__attribute__((used)) static int setup_ring(struct xenbus_device *dev, struct tpm_private *priv)
{
	struct xenbus_transaction xbt;
	const char *message = NULL;
	int rv;
	grant_ref_t gref;

	priv->shr = (void *)__get_free_page(GFP_KERNEL|__GFP_ZERO);
	if (!priv->shr) {
		xenbus_dev_fatal(dev, -ENOMEM, "allocating shared ring");
		return -ENOMEM;
	}

	rv = xenbus_grant_ring(dev, priv->shr, 1, &gref);
	if (rv < 0)
		return rv;

	priv->ring_ref = gref;

	rv = xenbus_alloc_evtchn(dev, &priv->evtchn);
	if (rv)
		return rv;

	rv = bind_evtchn_to_irqhandler(priv->evtchn, tpmif_interrupt, 0,
				       "tpmif", priv);
	if (rv <= 0) {
		xenbus_dev_fatal(dev, rv, "allocating TPM irq");
		return rv;
	}
	priv->irq = rv;

 again:
	rv = xenbus_transaction_start(&xbt);
	if (rv) {
		xenbus_dev_fatal(dev, rv, "starting transaction");
		return rv;
	}

	rv = xenbus_printf(xbt, dev->nodename,
			"ring-ref", "%u", priv->ring_ref);
	if (rv) {
		message = "writing ring-ref";
		goto abort_transaction;
	}

	rv = xenbus_printf(xbt, dev->nodename, "event-channel", "%u",
			priv->evtchn);
	if (rv) {
		message = "writing event-channel";
		goto abort_transaction;
	}

	rv = xenbus_printf(xbt, dev->nodename, "feature-protocol-v2", "1");
	if (rv) {
		message = "writing feature-protocol-v2";
		goto abort_transaction;
	}

	rv = xenbus_transaction_end(xbt, 0);
	if (rv == -EAGAIN)
		goto again;
	if (rv) {
		xenbus_dev_fatal(dev, rv, "completing transaction");
		return rv;
	}

	xenbus_switch_state(dev, XenbusStateInitialised);

	return 0;

 abort_transaction:
	xenbus_transaction_end(xbt, 1);
	if (message)
		xenbus_dev_error(dev, rv, "%s", message);

	return rv;
}