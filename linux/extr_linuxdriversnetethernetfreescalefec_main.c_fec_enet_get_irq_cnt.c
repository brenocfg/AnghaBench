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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int FEC_IRQ_NUM ; 
 int platform_irq_count (struct platform_device*) ; 

__attribute__((used)) static int fec_enet_get_irq_cnt(struct platform_device *pdev)
{
	int irq_cnt = platform_irq_count(pdev);

	if (irq_cnt > FEC_IRQ_NUM)
		irq_cnt = FEC_IRQ_NUM;	/* last for pps */
	else if (irq_cnt == 2)
		irq_cnt = 1;	/* last for pps */
	else if (irq_cnt <= 0)
		irq_cnt = 1;	/* At least 1 irq is needed */
	return irq_cnt;
}