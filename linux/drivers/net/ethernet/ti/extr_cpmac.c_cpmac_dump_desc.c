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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int /*<<< orphan*/  name; } ;
struct cpmac_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void cpmac_dump_desc(struct net_device *dev, struct cpmac_desc *desc)
{
	int i;

	printk("%s: desc[%p]:", dev->name, desc);
	for (i = 0; i < sizeof(*desc) / 4; i++)
		printk(" %08x", ((u32 *)desc)[i]);
	printk("\n");
}