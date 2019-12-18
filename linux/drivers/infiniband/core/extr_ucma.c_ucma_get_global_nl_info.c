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
struct ib_client_nl_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  abi; } ;
struct TYPE_2__ {int /*<<< orphan*/  this_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_USER_CM_ABI_VERSION ; 
 TYPE_1__ ucma_misc ; 

__attribute__((used)) static int ucma_get_global_nl_info(struct ib_client_nl_info *res)
{
	res->abi = RDMA_USER_CM_ABI_VERSION;
	res->cdev = ucma_misc.this_device;
	return 0;
}