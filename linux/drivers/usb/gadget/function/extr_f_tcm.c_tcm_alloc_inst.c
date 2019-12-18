#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_function_instance {int /*<<< orphan*/  group; int /*<<< orphan*/  free_func_inst; int /*<<< orphan*/  set_inst_name; } ;
struct f_tcm_opts {struct usb_function_instance func_inst; int /*<<< orphan*/  tcm_unregister_callback; int /*<<< orphan*/  tcm_register_callback; int /*<<< orphan*/  dep_lock; } ;
struct TYPE_2__ {struct usb_function_instance* func_inst; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_function_instance* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TPG_INSTANCES ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct f_tcm_opts*) ; 
 struct f_tcm_opts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcm_free_inst ; 
 int /*<<< orphan*/  tcm_func_type ; 
 int /*<<< orphan*/  tcm_register_callback ; 
 int /*<<< orphan*/  tcm_set_name ; 
 int /*<<< orphan*/  tcm_unregister_callback ; 
 TYPE_1__* tpg_instances ; 
 int /*<<< orphan*/  tpg_instances_lock ; 

__attribute__((used)) static struct usb_function_instance *tcm_alloc_inst(void)
{
	struct f_tcm_opts *opts;
	int i;


	opts = kzalloc(sizeof(*opts), GFP_KERNEL);
	if (!opts)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&tpg_instances_lock);
	for (i = 0; i < TPG_INSTANCES; ++i)
		if (!tpg_instances[i].func_inst)
			break;

	if (i == TPG_INSTANCES) {
		mutex_unlock(&tpg_instances_lock);
		kfree(opts);
		return ERR_PTR(-EBUSY);
	}
	tpg_instances[i].func_inst = &opts->func_inst;
	mutex_unlock(&tpg_instances_lock);

	mutex_init(&opts->dep_lock);
	opts->func_inst.set_inst_name = tcm_set_name;
	opts->func_inst.free_func_inst = tcm_free_inst;
	opts->tcm_register_callback = tcm_register_callback;
	opts->tcm_unregister_callback = tcm_unregister_callback;

	config_group_init_type_name(&opts->func_inst.group, "",
			&tcm_func_type);

	return &opts->func_inst;
}