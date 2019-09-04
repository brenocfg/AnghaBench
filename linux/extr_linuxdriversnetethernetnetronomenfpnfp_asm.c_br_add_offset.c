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
 scalar_t__ br_get_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_set_offset (int /*<<< orphan*/ *,scalar_t__) ; 

void br_add_offset(u64 *instr, u16 offset)
{
	u16 addr;

	addr = br_get_offset(*instr);
	br_set_offset(instr, addr + offset);
}