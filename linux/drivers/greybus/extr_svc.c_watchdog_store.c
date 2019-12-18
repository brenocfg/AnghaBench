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
struct gb_svc {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int gb_svc_watchdog_disable (struct gb_svc*) ; 
 int gb_svc_watchdog_enable (struct gb_svc*) ; 
 int strtobool (char const*,int*) ; 
 struct gb_svc* to_gb_svc (struct device*) ; 

__attribute__((used)) static ssize_t watchdog_store(struct device *dev,
			      struct device_attribute *attr, const char *buf,
			      size_t len)
{
	struct gb_svc *svc = to_gb_svc(dev);
	int retval;
	bool user_request;

	retval = strtobool(buf, &user_request);
	if (retval)
		return retval;

	if (user_request)
		retval = gb_svc_watchdog_enable(svc);
	else
		retval = gb_svc_watchdog_disable(svc);
	if (retval)
		return retval;
	return len;
}