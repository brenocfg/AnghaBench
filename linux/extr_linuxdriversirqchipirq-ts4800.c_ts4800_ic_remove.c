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
struct ts4800_irq_data {int /*<<< orphan*/  domain; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct ts4800_irq_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ts4800_ic_remove(struct platform_device *pdev)
{
	struct ts4800_irq_data *data = platform_get_drvdata(pdev);

	irq_domain_remove(data->domain);

	return 0;
}