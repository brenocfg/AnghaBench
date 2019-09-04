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
 int /*<<< orphan*/  TIF_HYBRID_FPREGS ; 
 int test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool hybrid_fprs(void)
{
	return test_thread_flag(TIF_HYBRID_FPREGS);
}