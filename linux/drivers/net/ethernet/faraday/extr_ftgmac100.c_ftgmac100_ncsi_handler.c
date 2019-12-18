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
struct ncsi_dev {scalar_t__ state; scalar_t__ link_up; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ncsi_dev_state_functional ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ftgmac100_ncsi_handler(struct ncsi_dev *nd)
{
	if (unlikely(nd->state != ncsi_dev_state_functional))
		return;

	netdev_dbg(nd->dev, "NCSI interface %s\n",
		   nd->link_up ? "up" : "down");
}