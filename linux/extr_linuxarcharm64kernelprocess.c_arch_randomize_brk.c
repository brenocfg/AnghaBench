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
struct mm_struct {int /*<<< orphan*/  brk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SZ_1G ; 
 int /*<<< orphan*/  SZ_32M ; 
 scalar_t__ is_compat_task () ; 
 unsigned long randomize_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned long arch_randomize_brk(struct mm_struct *mm)
{
	if (is_compat_task())
		return randomize_page(mm->brk, SZ_32M);
	else
		return randomize_page(mm->brk, SZ_1G);
}