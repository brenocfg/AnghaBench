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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_LOCKDEP_SUBCLASSES ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct i2c_adapter* i2c_parent_is_i2c_adapter (struct i2c_adapter*) ; 

unsigned int i2c_adapter_depth(struct i2c_adapter *adapter)
{
	unsigned int depth = 0;

	while ((adapter = i2c_parent_is_i2c_adapter(adapter)))
		depth++;

	WARN_ONCE(depth >= MAX_LOCKDEP_SUBCLASSES,
		  "adapter depth exceeds lockdep subclass limit\n");

	return depth;
}