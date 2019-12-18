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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  immed_can_modify (int /*<<< orphan*/ ) ; 
 scalar_t__ immed_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  immed_set_value (int /*<<< orphan*/ *,scalar_t__) ; 

void immed_add_value(u64 *instr, u16 offset)
{
	u16 val;

	if (!immed_can_modify(*instr))
		return;

	val = immed_get_value(*instr);
	immed_set_value(instr, val + offset);
}