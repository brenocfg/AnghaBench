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
struct TYPE_2__ {int /*<<< orphan*/  ngpio; } ;
struct pcf857x {TYPE_1__ chip; int /*<<< orphan*/  client; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 struct pcf857x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pcf857x_shutdown(struct i2c_client *client)
{
	struct pcf857x *gpio = i2c_get_clientdata(client);

	/* Drive all the I/O lines high */
	gpio->write(gpio->client, BIT(gpio->chip.ngpio) - 1);
}