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
struct tca6507_chip {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int tca6507_probe_gpios(struct i2c_client *client,
			       struct tca6507_chip *tca,
			       struct tca6507_platform_data *pdata)
{
	return 0;
}