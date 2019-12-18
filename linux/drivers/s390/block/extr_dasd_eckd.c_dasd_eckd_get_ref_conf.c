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
struct dasd_device {TYPE_1__* path; } ;
struct dasd_cuir_message {scalar_t__ record_selector; } ;
struct TYPE_4__ {scalar_t__ record_selector; } ;
struct dasd_conf_data {TYPE_2__ gneq; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_3__ {struct dasd_conf_data* conf_data; } ;

/* Variables and functions */
 size_t pathmask_to_pos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dasd_conf_data *dasd_eckd_get_ref_conf(struct dasd_device *device,
						     __u8 lpum,
						     struct dasd_cuir_message *cuir)
{
	struct dasd_conf_data *conf_data;
	int path, pos;

	if (cuir->record_selector == 0)
		goto out;
	for (path = 0x80, pos = 0; path; path >>= 1, pos++) {
		conf_data = device->path[pos].conf_data;
		if (conf_data->gneq.record_selector ==
		    cuir->record_selector)
			return conf_data;
	}
out:
	return device->path[pathmask_to_pos(lpum)].conf_data;
}