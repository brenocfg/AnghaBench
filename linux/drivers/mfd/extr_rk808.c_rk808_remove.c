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
struct rk808 {int /*<<< orphan*/ * pm_pwroff_prep_fn; int /*<<< orphan*/ * pm_pwroff_fn; int /*<<< orphan*/  irq_data; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct rk808* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/ * pm_power_off_prepare ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk808_remove(struct i2c_client *client)
{
	struct rk808 *rk808 = i2c_get_clientdata(client);

	regmap_del_irq_chip(client->irq, rk808->irq_data);

	/**
	 * pm_power_off may points to a function from another module.
	 * Check if the pointer is set by us and only then overwrite it.
	 */
	if (rk808->pm_pwroff_fn && pm_power_off == rk808->pm_pwroff_fn)
		pm_power_off = NULL;

	/**
	 * As above, check if the pointer is set by us before overwrite.
	 */
	if (rk808->pm_pwroff_prep_fn &&
	    pm_power_off_prepare == rk808->pm_pwroff_prep_fn)
		pm_power_off_prepare = NULL;

	return 0;
}