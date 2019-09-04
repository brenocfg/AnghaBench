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
struct men_z127_gpio {int /*<<< orphan*/  mem; int /*<<< orphan*/  reg_base; int /*<<< orphan*/  gc; } ;
struct mcb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct men_z127_gpio* mcb_get_drvdata (struct mcb_device*) ; 
 int /*<<< orphan*/  mcb_release_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void men_z127_remove(struct mcb_device *mdev)
{
	struct men_z127_gpio *men_z127_gpio = mcb_get_drvdata(mdev);

	gpiochip_remove(&men_z127_gpio->gc);
	iounmap(men_z127_gpio->reg_base);
	mcb_release_mem(men_z127_gpio->mem);
}