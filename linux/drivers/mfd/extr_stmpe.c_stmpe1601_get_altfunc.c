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
#define  STMPE_BLOCK_GPIO 130 
#define  STMPE_BLOCK_KEYPAD 129 
#define  STMPE_BLOCK_PWM 128 

__attribute__((used)) static int stmpe1601_get_altfunc(struct stmpe *stmpe, enum stmpe_block block)
{
	switch (block) {
	case STMPE_BLOCK_PWM:
		return 2;

	case STMPE_BLOCK_KEYPAD:
		return 1;

	case STMPE_BLOCK_GPIO:
	default:
		return 0;
	}
}