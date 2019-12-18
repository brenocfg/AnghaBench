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
typedef  enum stmpe_block { ____Placeholder_stmpe_block } stmpe_block ;

/* Variables and functions */
 int STMPE_BLOCK_TOUCHSCREEN ; 

__attribute__((used)) static int stmpe811_get_altfunc(struct stmpe *stmpe, enum stmpe_block block)
{
	/* 0 for touchscreen, 1 for GPIO */
	return block != STMPE_BLOCK_TOUCHSCREEN;
}