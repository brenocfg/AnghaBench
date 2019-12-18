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
struct vnt_rcb {scalar_t__ skb; scalar_t__ urb; } ;
struct vnt_private {int num_rcb; struct vnt_rcb** rcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct vnt_rcb*) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static void vnt_free_rx_bufs(struct vnt_private *priv)
{
	struct vnt_rcb *rcb;
	int ii;

	for (ii = 0; ii < priv->num_rcb; ii++) {
		rcb = priv->rcb[ii];
		if (!rcb)
			continue;

		/* deallocate URBs */
		if (rcb->urb) {
			usb_kill_urb(rcb->urb);
			usb_free_urb(rcb->urb);
		}

		/* deallocate skb */
		if (rcb->skb)
			dev_kfree_skb(rcb->skb);

		kfree(rcb);
	}
}