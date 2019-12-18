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
struct TYPE_2__ {int /*<<< orphan*/  coreid; } ;
struct ssb_device {TYPE_1__ id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*,char const*,char*) ; 

__attribute__((used)) static void print_irq(struct ssb_device *dev, unsigned int irq)
{
	static const char *irq_name[] = {"2(S)", "3", "4", "5", "6", "D", "I"};
	dev_dbg(dev->dev,
		"core 0x%04x, irq : %s%s %s%s %s%s %s%s %s%s %s%s %s%s\n",
		dev->id.coreid,
		irq_name[0], irq == 0 ? "*" : " ",
		irq_name[1], irq == 1 ? "*" : " ",
		irq_name[2], irq == 2 ? "*" : " ",
		irq_name[3], irq == 3 ? "*" : " ",
		irq_name[4], irq == 4 ? "*" : " ",
		irq_name[5], irq == 5 ? "*" : " ",
		irq_name[6], irq == 6 ? "*" : " ");
}