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
struct i2caux {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destruct (struct i2caux*) ; 
 int /*<<< orphan*/  kfree (struct i2caux*) ; 

__attribute__((used)) static void destroy(
	struct i2caux **i2c_engine)
{
	destruct(*i2c_engine);

	kfree(*i2c_engine);

	*i2c_engine = NULL;
}