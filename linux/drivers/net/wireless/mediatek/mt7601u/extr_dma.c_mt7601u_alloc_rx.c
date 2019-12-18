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
struct TYPE_4__ {int entries; TYPE_1__* e; struct mt7601u_dev* dev; } ;
struct mt7601u_dev {TYPE_2__ rx_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/  urb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MT_RX_ORDER ; 
 int N_RX_ENTRIES ; 
 int /*<<< orphan*/  dev_alloc_pages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7601u_alloc_rx(struct mt7601u_dev *dev)
{
	int i;

	memset(&dev->rx_q, 0, sizeof(dev->rx_q));
	dev->rx_q.dev = dev;
	dev->rx_q.entries = N_RX_ENTRIES;

	for (i = 0; i < N_RX_ENTRIES; i++) {
		dev->rx_q.e[i].urb = usb_alloc_urb(0, GFP_KERNEL);
		dev->rx_q.e[i].p = dev_alloc_pages(MT_RX_ORDER);

		if (!dev->rx_q.e[i].urb || !dev->rx_q.e[i].p)
			return -ENOMEM;
	}

	return 0;
}