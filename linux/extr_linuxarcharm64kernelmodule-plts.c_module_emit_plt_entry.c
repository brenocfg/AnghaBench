#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct plt_entry {int dummy; } ;
struct mod_plt_sec {int plt_num_entries; int plt_max_entries; TYPE_2__* plt; } ;
struct TYPE_7__ {struct mod_plt_sec init; struct mod_plt_sec core; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_10__ {scalar_t__ r_addend; } ;
struct TYPE_9__ {scalar_t__ st_value; } ;
struct TYPE_8__ {scalar_t__ sh_addr; } ;
typedef  TYPE_3__ Elf64_Sym ;
typedef  TYPE_4__ Elf64_Rela ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct plt_entry get_plt_entry (scalar_t__) ; 
 int /*<<< orphan*/  in_init (struct module*,void*) ; 
 scalar_t__ plt_entries_equal (struct plt_entry*,struct plt_entry*) ; 

u64 module_emit_plt_entry(struct module *mod, void *loc, const Elf64_Rela *rela,
			  Elf64_Sym *sym)
{
	struct mod_plt_sec *pltsec = !in_init(mod, loc) ? &mod->arch.core :
							  &mod->arch.init;
	struct plt_entry *plt = (struct plt_entry *)pltsec->plt->sh_addr;
	int i = pltsec->plt_num_entries;
	u64 val = sym->st_value + rela->r_addend;

	plt[i] = get_plt_entry(val);

	/*
	 * Check if the entry we just created is a duplicate. Given that the
	 * relocations are sorted, this will be the last entry we allocated.
	 * (if one exists).
	 */
	if (i > 0 && plt_entries_equal(plt + i, plt + i - 1))
		return (u64)&plt[i - 1];

	pltsec->plt_num_entries++;
	if (WARN_ON(pltsec->plt_num_entries > pltsec->plt_max_entries))
		return 0;

	return (u64)&plt[i];
}