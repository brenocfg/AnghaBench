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
struct stmpe {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct stmpe* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int stmpe_remove (struct stmpe*) ; 

__attribute__((used)) static int stmpe_i2c_remove(struct i2c_client *i2c)
{
	struct stmpe *stmpe = dev_get_drvdata(&i2c->dev);

	return stmpe_remove(stmpe);
}