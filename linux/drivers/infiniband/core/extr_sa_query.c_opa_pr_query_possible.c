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
typedef  int /*<<< orphan*/  u8 ;
struct sa_path_rec {int dummy; } ;
struct ib_sa_client {int dummy; } ;
struct ib_port_attr {scalar_t__ lid; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MULTICAST_LID_BASE ; 
 int PR_IB_SUPPORTED ; 
 int PR_NOT_SUPPORTED ; 
 int PR_OPA_SUPPORTED ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 scalar_t__ ib_sa_opa_pathrecord_support (struct ib_sa_client*,struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opa_pr_query_possible(struct ib_sa_client *client,
				 struct ib_device *device,
				 u8 port_num,
				 struct sa_path_rec *rec)
{
	struct ib_port_attr port_attr;

	if (ib_query_port(device, port_num, &port_attr))
		return PR_NOT_SUPPORTED;

	if (ib_sa_opa_pathrecord_support(client, device, port_num))
		return PR_OPA_SUPPORTED;

	if (port_attr.lid >= be16_to_cpu(IB_MULTICAST_LID_BASE))
		return PR_NOT_SUPPORTED;
	else
		return PR_IB_SUPPORTED;
}