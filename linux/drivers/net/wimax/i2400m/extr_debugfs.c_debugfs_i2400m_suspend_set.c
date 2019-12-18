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
typedef  int /*<<< orphan*/  u64 ;
struct i2400m {int dummy; } ;

/* Variables and functions */
 int i2400m_cmd_enter_powersave (struct i2400m*) ; 

__attribute__((used)) static
int debugfs_i2400m_suspend_set(void *data, u64 val)
{
	int result;
	struct i2400m *i2400m = data;
	result = i2400m_cmd_enter_powersave(i2400m);
	if (result >= 0)
		result = 0;
	return result;
}