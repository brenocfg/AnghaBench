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
struct crashtype {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  symbol_name; } ;
struct crashpoint {TYPE_1__ kprobe; } ;

/* Variables and functions */
 struct crashpoint* lkdtm_crashpoint ; 
 struct crashtype const* lkdtm_crashtype ; 
 int /*<<< orphan*/  lkdtm_do_action (struct crashtype const*) ; 
 TYPE_1__* lkdtm_kprobe ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int register_kprobe (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_kprobe (TYPE_1__*) ; 

__attribute__((used)) static int lkdtm_register_cpoint(struct crashpoint *crashpoint,
				 const struct crashtype *crashtype)
{
	int ret;

	/* If this doesn't have a symbol, just call immediately. */
	if (!crashpoint->kprobe.symbol_name) {
		lkdtm_do_action(crashtype);
		return 0;
	}

	if (lkdtm_kprobe != NULL)
		unregister_kprobe(lkdtm_kprobe);

	lkdtm_crashpoint = crashpoint;
	lkdtm_crashtype = crashtype;
	lkdtm_kprobe = &crashpoint->kprobe;
	ret = register_kprobe(lkdtm_kprobe);
	if (ret < 0) {
		pr_info("Couldn't register kprobe %s\n",
			crashpoint->kprobe.symbol_name);
		lkdtm_kprobe = NULL;
		lkdtm_crashpoint = NULL;
		lkdtm_crashtype = NULL;
	}

	return ret;
}