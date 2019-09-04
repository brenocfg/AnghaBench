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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct enic_port_profile {int set; int /*<<< orphan*/  host_uuid; int /*<<< orphan*/  instance_uuid; int /*<<< orphan*/  name; int /*<<< orphan*/  request; } ;
struct enic {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int ENIC_PORT_REQUEST_APPLIED ; 
 int /*<<< orphan*/  ENIC_PP_BY_INDEX (struct enic*,int,struct enic_port_profile*,int*) ; 
 int ENIC_SET_HOST ; 
 int ENIC_SET_INSTANCE ; 
 int ENIC_SET_NAME ; 
 int ENODATA ; 
 int /*<<< orphan*/  IFLA_PORT_HOST_UUID ; 
 int /*<<< orphan*/  IFLA_PORT_INSTANCE_UUID ; 
 int /*<<< orphan*/  IFLA_PORT_PROFILE ; 
 int /*<<< orphan*/  IFLA_PORT_REQUEST ; 
 int /*<<< orphan*/  IFLA_PORT_RESPONSE ; 
 int /*<<< orphan*/  PORT_PROFILE_MAX ; 
 int /*<<< orphan*/  PORT_PROFILE_RESPONSE_SUCCESS ; 
 int /*<<< orphan*/  PORT_UUID_MAX ; 
 int enic_process_get_pp_request (struct enic*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enic_get_vf_port(struct net_device *netdev, int vf,
	struct sk_buff *skb)
{
	struct enic *enic = netdev_priv(netdev);
	u16 response = PORT_PROFILE_RESPONSE_SUCCESS;
	struct enic_port_profile *pp;
	int err;

	ENIC_PP_BY_INDEX(enic, vf, pp, &err);
	if (err)
		return err;

	if (!(pp->set & ENIC_PORT_REQUEST_APPLIED))
		return -ENODATA;

	err = enic_process_get_pp_request(enic, vf, pp->request, &response);
	if (err)
		return err;

	if (nla_put_u16(skb, IFLA_PORT_REQUEST, pp->request) ||
	    nla_put_u16(skb, IFLA_PORT_RESPONSE, response) ||
	    ((pp->set & ENIC_SET_NAME) &&
	     nla_put(skb, IFLA_PORT_PROFILE, PORT_PROFILE_MAX, pp->name)) ||
	    ((pp->set & ENIC_SET_INSTANCE) &&
	     nla_put(skb, IFLA_PORT_INSTANCE_UUID, PORT_UUID_MAX,
		     pp->instance_uuid)) ||
	    ((pp->set & ENIC_SET_HOST) &&
	     nla_put(skb, IFLA_PORT_HOST_UUID, PORT_UUID_MAX, pp->host_uuid)))
		goto nla_put_failure;
	return 0;

nla_put_failure:
	return -EMSGSIZE;
}