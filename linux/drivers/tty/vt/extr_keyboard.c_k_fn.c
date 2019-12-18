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
struct vc_data {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__* func_table ; 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 
 int /*<<< orphan*/  puts_queue (struct vc_data*,scalar_t__) ; 

__attribute__((used)) static void k_fn(struct vc_data *vc, unsigned char value, char up_flag)
{
	if (up_flag)
		return;

	if ((unsigned)value < ARRAY_SIZE(func_table)) {
		if (func_table[value])
			puts_queue(vc, func_table[value]);
	} else
		pr_err("k_fn called with value=%d\n", value);
}