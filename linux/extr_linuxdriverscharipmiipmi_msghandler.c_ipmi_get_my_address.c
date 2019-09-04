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
struct ipmi_user {TYPE_2__* intf; } ;
struct TYPE_4__ {TYPE_1__* addrinfo; } ;
struct TYPE_3__ {unsigned char address; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 unsigned int IPMI_MAX_CHANNELS ; 
 struct ipmi_user* acquire_ipmi_user (struct ipmi_user*,int*) ; 
 unsigned int array_index_nospec (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 

int ipmi_get_my_address(struct ipmi_user *user,
			unsigned int  channel,
			unsigned char *address)
{
	int index, rv = 0;

	user = acquire_ipmi_user(user, &index);
	if (!user)
		return -ENODEV;

	if (channel >= IPMI_MAX_CHANNELS) {
		rv = -EINVAL;
	} else {
		channel = array_index_nospec(channel, IPMI_MAX_CHANNELS);
		*address = user->intf->addrinfo[channel].address;
	}
	release_ipmi_user(user, index);

	return rv;
}