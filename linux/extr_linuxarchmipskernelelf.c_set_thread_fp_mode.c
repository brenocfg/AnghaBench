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
 int /*<<< orphan*/  TIF_32BIT_FPREGS ; 
 int /*<<< orphan*/  TIF_HYBRID_FPREGS ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_thread_fp_mode(int hybrid, int regs32)
{
	if (hybrid)
		set_thread_flag(TIF_HYBRID_FPREGS);
	else
		clear_thread_flag(TIF_HYBRID_FPREGS);
	if (regs32)
		set_thread_flag(TIF_32BIT_FPREGS);
	else
		clear_thread_flag(TIF_32BIT_FPREGS);
}