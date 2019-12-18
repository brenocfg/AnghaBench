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
struct rt2x00_dev {int dummy; } ;
struct queue_entry_priv_usb_bcn {void* guardian_urb; void* urb; } ;
struct queue_entry_priv_usb {void* guardian_urb; void* urb; } ;
struct data_queue {unsigned int limit; scalar_t__ qid; TYPE_1__* entries; struct rt2x00_dev* rt2x00dev; } ;
struct TYPE_2__ {struct queue_entry_priv_usb_bcn* priv_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ QID_BEACON ; 
 int /*<<< orphan*/  REQUIRE_BEACON_GUARD ; 
 int /*<<< orphan*/  rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2x00usb_alloc_entries(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	struct queue_entry_priv_usb *entry_priv;
	struct queue_entry_priv_usb_bcn *bcn_priv;
	unsigned int i;

	for (i = 0; i < queue->limit; i++) {
		entry_priv = queue->entries[i].priv_data;
		entry_priv->urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!entry_priv->urb)
			return -ENOMEM;
	}

	/*
	 * If this is not the beacon queue or
	 * no guardian byte was required for the beacon,
	 * then we are done.
	 */
	if (queue->qid != QID_BEACON ||
	    !rt2x00_has_cap_flag(rt2x00dev, REQUIRE_BEACON_GUARD))
		return 0;

	for (i = 0; i < queue->limit; i++) {
		bcn_priv = queue->entries[i].priv_data;
		bcn_priv->guardian_urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!bcn_priv->guardian_urb)
			return -ENOMEM;
	}

	return 0;
}