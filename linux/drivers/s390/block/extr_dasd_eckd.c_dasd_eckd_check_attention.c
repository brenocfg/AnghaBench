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
struct dasd_device {int dummy; } ;
struct check_attention_work_data {int /*<<< orphan*/  worker; int /*<<< orphan*/  lpum; struct dasd_device* device; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eckd_check_attention_work ; 
 int /*<<< orphan*/  dasd_get_device (struct dasd_device*) ; 
 struct check_attention_work_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_eckd_check_attention(struct dasd_device *device, __u8 lpum)
{
	struct check_attention_work_data *data;

	data = kzalloc(sizeof(*data), GFP_ATOMIC);
	if (!data)
		return -ENOMEM;
	INIT_WORK(&data->worker, dasd_eckd_check_attention_work);
	dasd_get_device(device);
	data->device = device;
	data->lpum = lpum;
	schedule_work(&data->worker);
	return 0;
}