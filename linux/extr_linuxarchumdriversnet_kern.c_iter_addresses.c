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
struct net_device {struct in_device* ip_ptr; } ;
struct in_ifaddr {struct in_ifaddr* ifa_next; int /*<<< orphan*/  ifa_mask; int /*<<< orphan*/  ifa_address; } ;
struct in_device {struct in_ifaddr* ifa_list; } ;
typedef  int /*<<< orphan*/  netmask ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 void stub1 (unsigned char*,unsigned char*,void*) ; 

void iter_addresses(void *d, void (*cb)(unsigned char *, unsigned char *,
					void *),
		    void *arg)
{
	struct net_device *dev = d;
	struct in_device *ip = dev->ip_ptr;
	struct in_ifaddr *in;
	unsigned char address[4], netmask[4];

	if (ip == NULL) return;
	in = ip->ifa_list;
	while (in != NULL) {
		memcpy(address, &in->ifa_address, sizeof(address));
		memcpy(netmask, &in->ifa_mask, sizeof(netmask));
		(*cb)(address, netmask, arg);
		in = in->ifa_next;
	}
}