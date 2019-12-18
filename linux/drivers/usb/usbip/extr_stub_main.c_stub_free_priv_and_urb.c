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
struct urb {scalar_t__ num_sgs; int /*<<< orphan*/ * sg; struct urb** transfer_buffer; struct urb** setup_packet; } ;
struct stub_priv {int num_urbs; struct urb** urbs; int /*<<< orphan*/ * sgl; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct stub_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sgl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub_priv_cache ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

void stub_free_priv_and_urb(struct stub_priv *priv)
{
	struct urb *urb;
	int i;

	for (i = 0; i < priv->num_urbs; i++) {
		urb = priv->urbs[i];

		if (!urb)
			return;

		kfree(urb->setup_packet);
		urb->setup_packet = NULL;


		if (urb->transfer_buffer && !priv->sgl) {
			kfree(urb->transfer_buffer);
			urb->transfer_buffer = NULL;
		}

		if (urb->num_sgs) {
			sgl_free(urb->sg);
			urb->sg = NULL;
			urb->num_sgs = 0;
		}

		usb_free_urb(urb);
	}
	if (!list_empty(&priv->list))
		list_del(&priv->list);
	if (priv->sgl)
		sgl_free(priv->sgl);
	kfree(priv->urbs);
	kmem_cache_free(stub_priv_cache, priv);
}