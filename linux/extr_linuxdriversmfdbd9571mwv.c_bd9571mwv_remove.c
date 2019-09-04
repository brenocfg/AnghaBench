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
struct i2c_client {int dummy; } ;
struct bd9571mwv {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct bd9571mwv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bd9571mwv_remove(struct i2c_client *client)
{
	struct bd9571mwv *bd = i2c_get_clientdata(client);

	regmap_del_irq_chip(bd->irq, bd->irq_data);

	return 0;
}