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
struct mt7601u_tx_queue {int entries; TYPE_1__* e; struct mt7601u_dev* dev; } ;
struct mt7601u_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int N_TX_ENTRIES ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_alloc_tx_queue(struct mt7601u_dev *dev,
				  struct mt7601u_tx_queue *q)
{
	int i;

	q->dev = dev;
	q->entries = N_TX_ENTRIES;

	for (i = 0; i < N_TX_ENTRIES; i++) {
		q->e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!q->e[i].urb)
			return -ENOMEM;
	}

	return 0;
}