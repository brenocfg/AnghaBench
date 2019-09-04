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
struct tca6507_platform_data {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct tca6507_platform_data* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct tca6507_platform_data *
tca6507_led_dt_init(struct i2c_client *client)
{
	return ERR_PTR(-ENODEV);
}