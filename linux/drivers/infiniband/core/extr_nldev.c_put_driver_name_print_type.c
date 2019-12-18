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
struct sk_buff {int dummy; } ;
typedef  enum rdma_nldev_print_type { ____Placeholder_rdma_nldev_print_type } rdma_nldev_print_type ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DRIVER_PRINT_TYPE ; 
 int /*<<< orphan*/  RDMA_NLDEV_ATTR_DRIVER_STRING ; 
 int RDMA_NLDEV_PRINT_TYPE_UNSPEC ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int put_driver_name_print_type(struct sk_buff *msg, const char *name,
				      enum rdma_nldev_print_type print_type)
{
	if (nla_put_string(msg, RDMA_NLDEV_ATTR_DRIVER_STRING, name))
		return -EMSGSIZE;
	if (print_type != RDMA_NLDEV_PRINT_TYPE_UNSPEC &&
	    nla_put_u8(msg, RDMA_NLDEV_ATTR_DRIVER_PRINT_TYPE, print_type))
		return -EMSGSIZE;

	return 0;
}