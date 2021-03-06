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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
typedef  enum rdma_nldev_print_type { ____Placeholder_rdma_nldev_print_type } rdma_nldev_print_type ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DRIVER_U32 ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ put_driver_name_print_type (struct sk_buff*,char const*,int) ; 

__attribute__((used)) static int _rdma_nl_put_driver_u32(struct sk_buff *msg, const char *name,
				   enum rdma_nldev_print_type print_type,
				   u32 value)
{
	if (put_driver_name_print_type(msg, name, print_type))
		return -EMSGSIZE;
	if (nla_put_u32(msg, RDMA_NLDEV_ATTR_DRIVER_U32, value))
		return -EMSGSIZE;

	return 0;
}