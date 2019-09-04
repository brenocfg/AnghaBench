#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stub_entry {int dummy; } ;
struct TYPE_4__ {TYPE_1__* section; } ;
struct module {TYPE_2__ arch; } ;
struct TYPE_3__ {int stub_entries; } ;

/* Variables and functions */

unsigned int arch_mod_section_prepend(struct module *mod,
				      unsigned int section)
{
	/* size needed for all stubs of this section (including
	 * one additional for correct alignment of the stubs) */
	return (mod->arch.section[section].stub_entries + 1)
		* sizeof(struct stub_entry);
}