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
struct lp8788 {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct lp8788* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lp8788_irq_exit (struct lp8788*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp8788_remove(struct i2c_client *cl)
{
	struct lp8788 *lp = i2c_get_clientdata(cl);

	mfd_remove_devices(lp->dev);
	lp8788_irq_exit(lp);
	return 0;
}