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
struct pxa930_trkball {int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  input; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,struct pxa930_trkball*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa930_trkball*) ; 
 struct pxa930_trkball* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa930_trkball_remove(struct platform_device *pdev)
{
	struct pxa930_trkball *trkball = platform_get_drvdata(pdev);
	int irq = platform_get_irq(pdev, 0);

	input_unregister_device(trkball->input);
	free_irq(irq, trkball);
	iounmap(trkball->mmio_base);
	kfree(trkball);

	return 0;
}