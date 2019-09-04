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
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  SPRN_COUNTA ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  instruction_counter ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 get_insn_ctr(void)
{
	int ctr;
	unsigned long counta;

	do {
		ctr = atomic_read(&instruction_counter);
		counta = mfspr(SPRN_COUNTA);
	} while (ctr != atomic_read(&instruction_counter));

	return ((s64)ctr << 16) | (counta >> 16);
}