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
struct mt7601u_dev {int /*<<< orphan*/ * tx_q; } ;

/* Variables and functions */
 int __MT_EP_OUT_MAX ; 
 int /*<<< orphan*/  mt7601u_free_tx_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt7601u_free_tx(struct mt7601u_dev *dev)
{
	int i;

	if (!dev->tx_q)
		return;

	for (i = 0; i < __MT_EP_OUT_MAX; i++)
		mt7601u_free_tx_queue(&dev->tx_q[i]);
}