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
struct usb3503 {int /*<<< orphan*/  clk; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct usb3503* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int usb3503_i2c_remove(struct i2c_client *i2c)
{
	struct usb3503 *hub;

	hub = i2c_get_clientdata(i2c);
	clk_disable_unprepare(hub->clk);

	return 0;
}