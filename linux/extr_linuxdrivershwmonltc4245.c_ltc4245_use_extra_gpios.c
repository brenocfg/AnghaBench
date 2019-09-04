#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ltc4245_platform_data {int use_extra_gpios; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct ltc4245_platform_data* dev_get_platdata (TYPE_1__*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ltc4245_use_extra_gpios(struct i2c_client *client)
{
	struct ltc4245_platform_data *pdata = dev_get_platdata(&client->dev);
	struct device_node *np = client->dev.of_node;

	/* prefer platform data */
	if (pdata)
		return pdata->use_extra_gpios;

	/* fallback on OF */
	if (of_find_property(np, "ltc4245,use-extra-gpios", NULL))
		return true;

	return false;
}