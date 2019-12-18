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
struct lp8727_chg {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct lp8727_chg* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lp8727_release_irq (struct lp8727_chg*) ; 
 int /*<<< orphan*/  lp8727_unregister_psy (struct lp8727_chg*) ; 

__attribute__((used)) static int lp8727_remove(struct i2c_client *cl)
{
	struct lp8727_chg *pchg = i2c_get_clientdata(cl);

	lp8727_release_irq(pchg);
	lp8727_unregister_psy(pchg);
	return 0;
}