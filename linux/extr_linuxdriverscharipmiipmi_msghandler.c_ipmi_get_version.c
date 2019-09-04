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
struct ipmi_user {int /*<<< orphan*/  intf; } ;
struct ipmi_device_id {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 int bmc_get_device_id (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ipmi_device_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char ipmi_version_major (struct ipmi_device_id*) ; 
 unsigned char ipmi_version_minor (struct ipmi_device_id*) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 

int ipmi_get_version(struct ipmi_user *user,
		     unsigned char *major,
		     unsigned char *minor)
{
	struct ipmi_device_id id;
	int rv, index;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	rv = bmc_get_device_id(user->intf, NULL, &id, NULL, NULL);
	if (!rv) {
		*major = ipmi_version_major(&id);
		*minor = ipmi_version_minor(&id);
	}
	release_ipmi_user(user, index);

	return rv;
}