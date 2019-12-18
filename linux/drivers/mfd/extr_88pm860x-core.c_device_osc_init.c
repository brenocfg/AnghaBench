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
struct pm860x_chip {int /*<<< orphan*/  osc_status; int /*<<< orphan*/  osc_vote; int /*<<< orphan*/  osc_lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM8606_MISC ; 
 int /*<<< orphan*/  PM8606_MISC_OSC_EN ; 
 int /*<<< orphan*/  PM8606_REF_GP_OSC_OFF ; 
 int /*<<< orphan*/  PM8606_VSYS ; 
 int /*<<< orphan*/  PM8606_VSYS_EN ; 
 int /*<<< orphan*/  REF_GP_NO_CLIENTS ; 
 struct pm860x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm860x_set_bits (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void device_osc_init(struct i2c_client *i2c)
{
	struct pm860x_chip *chip = i2c_get_clientdata(i2c);

	mutex_init(&chip->osc_lock);
	/* init portofino reference group voting and status */
	/* Disable Reference group Vsys */
	pm860x_set_bits(i2c, PM8606_VSYS, PM8606_VSYS_EN, 0);
	/* Disable Internal Oscillator */
	pm860x_set_bits(i2c, PM8606_MISC, PM8606_MISC_OSC_EN, 0);

	chip->osc_vote = REF_GP_NO_CLIENTS;
	chip->osc_status = PM8606_REF_GP_OSC_OFF;
}