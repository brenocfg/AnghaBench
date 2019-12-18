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

/* Variables and functions */
 scalar_t__ FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IMMED_WIDTH_ALL ; 
 int /*<<< orphan*/  OP_IMMED_INV ; 
 int /*<<< orphan*/  OP_IMMED_SHIFT ; 
 int /*<<< orphan*/  OP_IMMED_WIDTH ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static bool immed_can_modify(u64 instr)
{
	if (FIELD_GET(OP_IMMED_INV, instr) ||
	    FIELD_GET(OP_IMMED_SHIFT, instr) ||
	    FIELD_GET(OP_IMMED_WIDTH, instr) != IMMED_WIDTH_ALL) {
		pr_err("Can't decode/encode immed!\n");
		return false;
	}
	return true;
}