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
struct arche_platform_drvdata {int /*<<< orphan*/  wake_detect_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void arche_platform_wd_irq_en(struct arche_platform_drvdata *arche_pdata)
{
	/* Enable interrupt here, to read event back from SVC */
	enable_irq(arche_pdata->wake_detect_irq);
}