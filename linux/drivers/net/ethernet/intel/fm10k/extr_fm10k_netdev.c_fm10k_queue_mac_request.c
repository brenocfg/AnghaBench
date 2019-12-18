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
typedef  void* u16 ;
struct TYPE_2__ {void* vid; void* glort; int /*<<< orphan*/  addr; } ;
struct fm10k_macvlan_request {int set; int /*<<< orphan*/  list; TYPE_1__ mac; int /*<<< orphan*/  type; } ;
struct fm10k_intfc {int /*<<< orphan*/  macvlan_lock; int /*<<< orphan*/  macvlan_requests; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FM10K_MC_MAC_REQUEST ; 
 int /*<<< orphan*/  FM10K_UC_MAC_REQUEST ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  fm10k_macvlan_schedule (struct fm10k_intfc*) ; 
 scalar_t__ is_multicast_ether_addr (unsigned char const*) ; 
 struct fm10k_macvlan_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int fm10k_queue_mac_request(struct fm10k_intfc *interface, u16 glort,
			    const unsigned char *addr, u16 vid, bool set)
{
	struct fm10k_macvlan_request *request;
	unsigned long flags;

	/* This must be atomic since we may be called while the netdev
	 * addr_list_lock is held
	 */
	request = kzalloc(sizeof(*request), GFP_ATOMIC);
	if (!request)
		return -ENOMEM;

	if (is_multicast_ether_addr(addr))
		request->type = FM10K_MC_MAC_REQUEST;
	else
		request->type = FM10K_UC_MAC_REQUEST;

	ether_addr_copy(request->mac.addr, addr);
	request->mac.glort = glort;
	request->mac.vid = vid;
	request->set = set;

	spin_lock_irqsave(&interface->macvlan_lock, flags);
	list_add_tail(&request->list, &interface->macvlan_requests);
	spin_unlock_irqrestore(&interface->macvlan_lock, flags);

	fm10k_macvlan_schedule(interface);

	return 0;
}