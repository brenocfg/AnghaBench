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
struct kobj_uevent_env {int dummy; } ;
struct device {int dummy; } ;
struct ccw_device_id {char* cu_type; char* cu_model; char* dev_type; char* dev_model; } ;
struct ccw_device {struct ccw_device_id id; } ;
typedef  int /*<<< orphan*/  modalias_buf ;

/* Variables and functions */
 int add_uevent_var (struct kobj_uevent_env*,char*,char*) ; 
 int /*<<< orphan*/  snprint_alias (char*,int,struct ccw_device_id*,char*) ; 
 struct ccw_device* to_ccwdev (struct device*) ; 

__attribute__((used)) static int ccw_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	struct ccw_device *cdev = to_ccwdev(dev);
	struct ccw_device_id *id = &(cdev->id);
	int ret;
	char modalias_buf[30];

	/* CU_TYPE= */
	ret = add_uevent_var(env, "CU_TYPE=%04X", id->cu_type);
	if (ret)
		return ret;

	/* CU_MODEL= */
	ret = add_uevent_var(env, "CU_MODEL=%02X", id->cu_model);
	if (ret)
		return ret;

	/* The next two can be zero, that's ok for us */
	/* DEV_TYPE= */
	ret = add_uevent_var(env, "DEV_TYPE=%04X", id->dev_type);
	if (ret)
		return ret;

	/* DEV_MODEL= */
	ret = add_uevent_var(env, "DEV_MODEL=%02X", id->dev_model);
	if (ret)
		return ret;

	/* MODALIAS=  */
	snprint_alias(modalias_buf, sizeof(modalias_buf), id, "");
	ret = add_uevent_var(env, "MODALIAS=%s", modalias_buf);
	return ret;
}