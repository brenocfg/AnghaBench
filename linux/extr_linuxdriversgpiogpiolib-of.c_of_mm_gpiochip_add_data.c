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
struct gpio_chip {int base; int /*<<< orphan*/  label; struct device_node* of_node; } ;
struct of_mm_gpio_chip {int /*<<< orphan*/  regs; struct gpio_chip gc; int /*<<< orphan*/  (* save_regs ) (struct of_mm_gpio_chip*) ;} ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int gpiochip_add_data (struct gpio_chip*,void*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct device_node*,int) ; 
 int /*<<< orphan*/  stub1 (struct of_mm_gpio_chip*) ; 

int of_mm_gpiochip_add_data(struct device_node *np,
			    struct of_mm_gpio_chip *mm_gc,
			    void *data)
{
	int ret = -ENOMEM;
	struct gpio_chip *gc = &mm_gc->gc;

	gc->label = kasprintf(GFP_KERNEL, "%pOF", np);
	if (!gc->label)
		goto err0;

	mm_gc->regs = of_iomap(np, 0);
	if (!mm_gc->regs)
		goto err1;

	gc->base = -1;

	if (mm_gc->save_regs)
		mm_gc->save_regs(mm_gc);

	mm_gc->gc.of_node = np;

	ret = gpiochip_add_data(gc, data);
	if (ret)
		goto err2;

	return 0;
err2:
	iounmap(mm_gc->regs);
err1:
	kfree(gc->label);
err0:
	pr_err("%pOF: GPIO chip registration failed with status %d\n", np, ret);
	return ret;
}