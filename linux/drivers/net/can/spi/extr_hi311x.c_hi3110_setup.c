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
 int /*<<< orphan*/  hi3110_do_set_bittiming (struct net_device*) ; 

__attribute__((used)) static int hi3110_setup(struct net_device *net)
{
	hi3110_do_set_bittiming(net);
	return 0;
}