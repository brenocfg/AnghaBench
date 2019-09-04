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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atom_op_debug(atom_exec_context *ctx, int *ptr, int arg)
{
	uint8_t val = U8((*ptr)++);
	SDEBUG("DEBUG output: 0x%02X\n", val);
}