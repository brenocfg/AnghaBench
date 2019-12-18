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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_NLDEV_PRINT_TYPE_HEX ; 
 int _rdma_nl_put_driver_u64 (struct sk_buff*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rdma_nl_put_driver_u64_hex(struct sk_buff *msg, const char *name, u64 value)
{
	return _rdma_nl_put_driver_u64(msg, name, RDMA_NLDEV_PRINT_TYPE_HEX,
				       value);
}