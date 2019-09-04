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

/* Variables and functions */
 int /*<<< orphan*/  DEST_RM ; 
 int /*<<< orphan*/  FPU_rm ; 
 int /*<<< orphan*/  FPU_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_C1 () ; 
 int /*<<< orphan*/  control_word ; 

void fsubri(void)
{
	/* fsubr st(i),st */
	clear_C1();
	FPU_sub(DEST_RM, FPU_rm, control_word);
}