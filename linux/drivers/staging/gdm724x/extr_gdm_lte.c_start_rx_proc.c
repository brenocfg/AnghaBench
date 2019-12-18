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
struct phy_dev {int /*<<< orphan*/  priv_dev; int /*<<< orphan*/  (* rcv_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct phy_dev*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_RX_SUBMIT_COUNT ; 
 int /*<<< orphan*/  USB_COMPLETE ; 
 int /*<<< orphan*/  rx_complete ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct phy_dev*,int /*<<< orphan*/ ) ; 

void start_rx_proc(struct phy_dev *phy_dev)
{
	int i;

	for (i = 0; i < MAX_RX_SUBMIT_COUNT; i++)
		phy_dev->rcv_func(phy_dev->priv_dev,
				rx_complete, phy_dev, USB_COMPLETE);
}