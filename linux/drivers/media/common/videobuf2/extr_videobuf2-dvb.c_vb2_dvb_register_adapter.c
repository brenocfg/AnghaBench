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
struct TYPE_2__ {int mfe_shared; struct media_device* mdev; void* priv; } ;
struct vb2_dvb_frontends {TYPE_1__ adapter; int /*<<< orphan*/  lock; } ;
struct module {int dummy; } ;
struct media_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int dvb_register_adapter (TYPE_1__*,char*,struct module*,struct device*,short*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int) ; 

__attribute__((used)) static int vb2_dvb_register_adapter(struct vb2_dvb_frontends *fe,
			  struct module *module,
			  void *adapter_priv,
			  struct device *device,
			  struct media_device *mdev,
			  char *adapter_name,
			  short *adapter_nr,
			  int mfe_shared)
{
	int result;

	mutex_init(&fe->lock);

	/* register adapter */
	result = dvb_register_adapter(&fe->adapter, adapter_name, module,
		device, adapter_nr);
	if (result < 0) {
		pr_warn("%s: dvb_register_adapter failed (errno = %d)\n",
		       adapter_name, result);
	}
	fe->adapter.priv = adapter_priv;
	fe->adapter.mfe_shared = mfe_shared;
#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	if (mdev)
		fe->adapter.mdev = mdev;
#endif
	return result;
}