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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  atom_exec_context ;

/* Variables and functions */
 int /*<<< orphan*/  SDEBUG (char*,scalar_t__) ; 
 scalar_t__ U16 (int) ; 

__attribute__((used)) static void atom_op_processds(atom_exec_context *ctx, int *ptr, int arg)
{
	uint16_t val = U16(*ptr);
	(*ptr) += val + 2;
	SDEBUG("PROCESSDS output: 0x%02X\n", val);
}