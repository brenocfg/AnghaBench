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
struct rj54n1 {int /*<<< orphan*/  subdev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  clk; scalar_t__ pwup_gpio; scalar_t__ enable_gpio; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rj54n1_remove(struct i2c_client *client)
{
	struct rj54n1 *rj54n1 = to_rj54n1(client);

	if (rj54n1->enable_gpio)
		gpiod_put(rj54n1->enable_gpio);
	if (rj54n1->pwup_gpio)
		gpiod_put(rj54n1->pwup_gpio);

	clk_put(rj54n1->clk);
	v4l2_ctrl_handler_free(&rj54n1->hdl);
	v4l2_async_unregister_subdev(&rj54n1->subdev);

	return 0;
}