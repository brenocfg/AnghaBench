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
 int /*<<< orphan*/  cvm_oct_common_init (struct net_device*) ; 

int cvm_oct_sgmii_init(struct net_device *dev)
{
	cvm_oct_common_init(dev);

	/* FIXME: Need autoneg logic */
	return 0;
}