#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ r_info; scalar_t__ r_addend; } ;
typedef  TYPE_1__ Elf64_Rela ;

/* Variables and functions */

__attribute__((used)) static int is_rela_equal(const Elf64_Rela *x, const Elf64_Rela *y)
{
	return x->r_info == y->r_info && x->r_addend == y->r_addend;
}