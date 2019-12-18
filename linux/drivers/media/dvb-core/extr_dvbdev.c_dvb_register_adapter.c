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
struct dvb_adapter {int num; char const* name; int /*<<< orphan*/  list_head; int /*<<< orphan*/  mdev_lock; int /*<<< orphan*/  mfe_lock; int /*<<< orphan*/ * mfe_dvbdev; scalar_t__ mfe_shared; struct device* device; struct module* module; int /*<<< orphan*/  device_list; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DVB_MAX_ADAPTERS ; 
 int ENFILE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_adapter_list ; 
 scalar_t__ dvbdev_check_free_adapter_num (int) ; 
 int dvbdev_get_free_adapter_num () ; 
 int /*<<< orphan*/  dvbdev_register_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct dvb_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 

int dvb_register_adapter(struct dvb_adapter *adap, const char *name,
			 struct module *module, struct device *device,
			 short *adapter_nums)
{
	int i, num;

	mutex_lock(&dvbdev_register_lock);

	for (i = 0; i < DVB_MAX_ADAPTERS; ++i) {
		num = adapter_nums[i];
		if (num >= 0  &&  num < DVB_MAX_ADAPTERS) {
		/* use the one the driver asked for */
			if (dvbdev_check_free_adapter_num(num))
				break;
		} else {
			num = dvbdev_get_free_adapter_num();
			break;
		}
		num = -1;
	}

	if (num < 0) {
		mutex_unlock(&dvbdev_register_lock);
		return -ENFILE;
	}

	memset (adap, 0, sizeof(struct dvb_adapter));
	INIT_LIST_HEAD (&adap->device_list);

	pr_info("DVB: registering new adapter (%s)\n", name);

	adap->num = num;
	adap->name = name;
	adap->module = module;
	adap->device = device;
	adap->mfe_shared = 0;
	adap->mfe_dvbdev = NULL;
	mutex_init (&adap->mfe_lock);

#ifdef CONFIG_MEDIA_CONTROLLER_DVB
	mutex_init(&adap->mdev_lock);
#endif

	list_add_tail (&adap->list_head, &dvb_adapter_list);

	mutex_unlock(&dvbdev_register_lock);

	return num;
}