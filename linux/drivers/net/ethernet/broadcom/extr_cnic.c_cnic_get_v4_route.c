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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct dst_entry {int dummy; } ;
struct rtable {struct dst_entry dst; } ;

/* Variables and functions */
 int ENETUNREACH ; 
 int /*<<< orphan*/  IS_ERR (struct rtable*) ; 
 int PTR_ERR (struct rtable*) ; 
 int /*<<< orphan*/  init_net ; 
 struct rtable* ip_route_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cnic_get_v4_route(struct sockaddr_in *dst_addr,
			     struct dst_entry **dst)
{
#if defined(CONFIG_INET)
	struct rtable *rt;

	rt = ip_route_output(&init_net, dst_addr->sin_addr.s_addr, 0, 0, 0);
	if (!IS_ERR(rt)) {
		*dst = &rt->dst;
		return 0;
	}
	return PTR_ERR(rt);
#else
	return -ENETUNREACH;
#endif
}