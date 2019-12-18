#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_gvt {int dummy; } ;
struct cmd_info {int /*<<< orphan*/  name; } ;
struct cmd_entry {TYPE_1__* info; int /*<<< orphan*/  hlist; } ;
struct TYPE_3__ {unsigned int devices; scalar_t__ opcode; int /*<<< orphan*/  rings; int /*<<< orphan*/  flag; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 scalar_t__ OP_MI_NOOP ; 
 int /*<<< orphan*/  add_cmd_entry (struct intel_gvt*,struct cmd_entry*) ; 
 TYPE_1__* cmd_info ; 
 struct cmd_info* find_cmd_entry_any_ring (struct intel_gvt*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_dbg_cmd (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvt_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int intel_gvt_get_device_type (struct intel_gvt*) ; 
 int /*<<< orphan*/  kfree (struct cmd_entry*) ; 
 struct cmd_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mi_noop_index ; 

__attribute__((used)) static int init_cmd_table(struct intel_gvt *gvt)
{
	int i;
	struct cmd_entry *e;
	const struct cmd_info *info;
	unsigned int gen_type;

	gen_type = intel_gvt_get_device_type(gvt);

	for (i = 0; i < ARRAY_SIZE(cmd_info); i++) {
		if (!(cmd_info[i].devices & gen_type))
			continue;

		e = kzalloc(sizeof(*e), GFP_KERNEL);
		if (!e)
			return -ENOMEM;

		e->info = &cmd_info[i];
		info = find_cmd_entry_any_ring(gvt,
				e->info->opcode, e->info->rings);
		if (info) {
			gvt_err("%s %s duplicated\n", e->info->name,
					info->name);
			kfree(e);
			return -EEXIST;
		}
		if (cmd_info[i].opcode == OP_MI_NOOP)
			mi_noop_index = i;

		INIT_HLIST_NODE(&e->hlist);
		add_cmd_entry(gvt, e);
		gvt_dbg_cmd("add %-30s op %04x flag %x devs %02x rings %02x\n",
				e->info->name, e->info->opcode, e->info->flag,
				e->info->devices, e->info->rings);
	}
	return 0;
}