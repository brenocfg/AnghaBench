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
struct module {int dummy; } ;
struct firmware_work {void (* cont ) (struct firmware const*,void*) ;int opt_flags; int /*<<< orphan*/  work; struct device* device; int /*<<< orphan*/  name; void* context; struct module* module; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int FW_OPT_NOWAIT ; 
 int FW_OPT_UEVENT ; 
 int FW_OPT_USERHELPER ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fw_cache_is_setup (struct device*,char const*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct firmware_work*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 struct firmware_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_firmware_work_func ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (struct module*) ; 

int
request_firmware_nowait(
	struct module *module, bool uevent,
	const char *name, struct device *device, gfp_t gfp, void *context,
	void (*cont)(const struct firmware *fw, void *context))
{
	struct firmware_work *fw_work;

	fw_work = kzalloc(sizeof(struct firmware_work), gfp);
	if (!fw_work)
		return -ENOMEM;

	fw_work->module = module;
	fw_work->name = kstrdup_const(name, gfp);
	if (!fw_work->name) {
		kfree(fw_work);
		return -ENOMEM;
	}
	fw_work->device = device;
	fw_work->context = context;
	fw_work->cont = cont;
	fw_work->opt_flags = FW_OPT_NOWAIT |
		(uevent ? FW_OPT_UEVENT : FW_OPT_USERHELPER);

	if (!uevent && fw_cache_is_setup(device, name)) {
		kfree_const(fw_work->name);
		kfree(fw_work);
		return -EOPNOTSUPP;
	}

	if (!try_module_get(module)) {
		kfree_const(fw_work->name);
		kfree(fw_work);
		return -EFAULT;
	}

	get_device(fw_work->device);
	INIT_WORK(&fw_work->work, request_firmware_work_func);
	schedule_work(&fw_work->work);
	return 0;
}