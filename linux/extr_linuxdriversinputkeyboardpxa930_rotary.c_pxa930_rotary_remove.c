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
struct pxa930_rotary {int /*<<< orphan*/  mmio_base; int /*<<< orphan*/  input_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pxa930_rotary*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pxa930_rotary*) ; 
 struct pxa930_rotary* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pxa930_rotary_remove(struct platform_device *pdev)
{
	struct pxa930_rotary *r = platform_get_drvdata(pdev);

	free_irq(platform_get_irq(pdev, 0), r);
	input_unregister_device(r->input_dev);
	iounmap(r->mmio_base);
	kfree(r);

	return 0;
}