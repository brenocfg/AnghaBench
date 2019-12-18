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
typedef  int /*<<< orphan*/  u8 ;
struct flowi6 {int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct dst_entry {scalar_t__ error; } ;
struct cxgb4_lld_info {int dummy; } ;
typedef  int /*<<< orphan*/  fl6 ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {TYPE_2__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int IFF_LOOPBACK ; 
 int IPV6_ADDR_LINKLOCAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_our_interface (struct cxgb4_lld_info*,struct net_device* (*) (struct net_device*),TYPE_2__*) ; 
 int /*<<< orphan*/  dst_release (struct dst_entry*) ; 
 int /*<<< orphan*/  init_net ; 
 TYPE_1__* ip6_dst_idev (struct dst_entry*) ; 
 struct dst_entry* ip6_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct flowi6*) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 

struct dst_entry *
cxgb_find_route6(struct cxgb4_lld_info *lldi,
		 struct net_device *(*get_real_dev)(struct net_device *),
		 __u8 *local_ip, __u8 *peer_ip, __be16 local_port,
		 __be16 peer_port, u8 tos, __u32 sin6_scope_id)
{
	struct dst_entry *dst = NULL;

	if (IS_ENABLED(CONFIG_IPV6)) {
		struct flowi6 fl6;

		memset(&fl6, 0, sizeof(fl6));
		memcpy(&fl6.daddr, peer_ip, 16);
		memcpy(&fl6.saddr, local_ip, 16);
		if (ipv6_addr_type(&fl6.daddr) & IPV6_ADDR_LINKLOCAL)
			fl6.flowi6_oif = sin6_scope_id;
		dst = ip6_route_output(&init_net, NULL, &fl6);
		if (dst->error ||
		    (!cxgb_our_interface(lldi, get_real_dev,
					 ip6_dst_idev(dst)->dev) &&
		     !(ip6_dst_idev(dst)->dev->flags & IFF_LOOPBACK))) {
			dst_release(dst);
			return NULL;
		}
	}

	return dst;
}