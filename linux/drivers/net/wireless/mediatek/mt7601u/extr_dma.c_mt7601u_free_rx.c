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
struct TYPE_4__ {int entries; TYPE_1__* e; } ;
struct mt7601u_dev {TYPE_2__ rx_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  urb; int /*<<< orphan*/  p; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_RX_ORDER ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7601u_free_rx(struct mt7601u_dev *dev)
{
	int i;

	for (i = 0; i < dev->rx_q.entries; i++) {
		__free_pages(dev->rx_q.e[i].p, MT_RX_ORDER);
		usb_free_urb(dev->rx_q.e[i].urb);
	}
}