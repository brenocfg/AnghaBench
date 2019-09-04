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
typedef  int /*<<< orphan*/  u32 ;
struct module {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  Elf_Addr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apply_r_riscv_align_rela(struct module *me, u32 *location,
				    Elf_Addr v)
{
	pr_err(
	  "%s: The unexpected relocation type 'R_RISCV_ALIGN' from PC = %p\n",
	  me->name, location);
	return -EINVAL;
}