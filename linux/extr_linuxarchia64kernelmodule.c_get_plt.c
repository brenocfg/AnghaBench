#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct plt_entry {scalar_t__** bundle; } ;
struct TYPE_6__ {TYPE_2__* core_plt; TYPE_1__* init_plt; } ;
struct module {TYPE_3__ arch; } ;
struct insn {int dummy; } ;
struct TYPE_5__ {int sh_size; scalar_t__ sh_addr; } ;
struct TYPE_4__ {int sh_size; scalar_t__ sh_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct plt_entry ia64_plt_template ; 
 scalar_t__ in_init (struct module*,scalar_t__) ; 
 int /*<<< orphan*/  patch_plt (struct module*,struct plt_entry*,scalar_t__,scalar_t__) ; 
 scalar_t__ plt_target (struct plt_entry*) ; 

__attribute__((used)) static uint64_t
get_plt (struct module *mod, const struct insn *insn, uint64_t value, int *okp)
{
	struct plt_entry *plt, *plt_end;
	uint64_t target_ip, target_gp;

	if (!*okp)
		return 0;

	if (in_init(mod, (uint64_t) insn)) {
		plt = (void *) mod->arch.init_plt->sh_addr;
		plt_end = (void *) plt + mod->arch.init_plt->sh_size;
	} else {
		plt = (void *) mod->arch.core_plt->sh_addr;
		plt_end = (void *) plt + mod->arch.core_plt->sh_size;
	}

	/* "value" is a pointer to a function-descriptor; fetch the target ip/gp from it: */
	target_ip = ((uint64_t *) value)[0];
	target_gp = ((uint64_t *) value)[1];

	/* Look for existing PLT entry. */
	while (plt->bundle[0][0]) {
		if (plt_target(plt) == target_ip)
			goto found;
		if (++plt >= plt_end)
			BUG();
	}
	*plt = ia64_plt_template;
	if (!patch_plt(mod, plt, target_ip, target_gp)) {
		*okp = 0;
		return 0;
	}
#if ARCH_MODULE_DEBUG
	if (plt_target(plt) != target_ip) {
		printk("%s: mistargeted PLT: wanted %lx, got %lx\n",
		       __func__, target_ip, plt_target(plt));
		*okp = 0;
		return 0;
	}
#endif
  found:
	return (uint64_t) plt;
}