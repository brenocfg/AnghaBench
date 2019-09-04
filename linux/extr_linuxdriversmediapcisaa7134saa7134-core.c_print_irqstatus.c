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
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 unsigned int IRQBITS ; 
 unsigned long SAA7134_IRQ_REPORT_DONE_RA0 ; 
 int /*<<< orphan*/  irq_dbg (int,char*,int,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/ * irqbits ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static void print_irqstatus(struct saa7134_dev *dev, int loop,
			    unsigned long report, unsigned long status)
{
	unsigned int i;

	irq_dbg(1, "[%d,%ld]: r=0x%lx s=0x%02lx",
		loop, jiffies, report, status);
	for (i = 0; i < IRQBITS; i++) {
		if (!(report & (1 << i)))
			continue;
		pr_cont(" %s", irqbits[i]);
	}
	if (report & SAA7134_IRQ_REPORT_DONE_RA0) {
		pr_cont(" | RA0=%s,%s,%s,%ld",
			(status & 0x40) ? "vbi"  : "video",
			(status & 0x20) ? "b"    : "a",
			(status & 0x10) ? "odd"  : "even",
			(status & 0x0f));
	}
	pr_cont("\n");
}