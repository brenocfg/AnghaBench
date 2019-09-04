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
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipi_flush_tlb_mm ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mm_struct*,int) ; 

void flush_tlb_mm(struct mm_struct *mm)
{
	on_each_cpu(ipi_flush_tlb_mm, mm, 1);
}