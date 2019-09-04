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
struct mm_struct {int /*<<< orphan*/  pgd; } ;

/* Variables and functions */
 int /*<<< orphan*/  __xen_pgd_pin (struct mm_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_pgd_pin(struct mm_struct *mm)
{
	__xen_pgd_pin(mm, mm->pgd);
}