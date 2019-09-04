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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_rxmode (struct net_device*,int,int) ; 

__attribute__((used)) static void cxgb4vf_set_rxmode(struct net_device *dev)
{
	/* unfortunately we can't return errors to the stack */
	set_rxmode(dev, -1, false);
}