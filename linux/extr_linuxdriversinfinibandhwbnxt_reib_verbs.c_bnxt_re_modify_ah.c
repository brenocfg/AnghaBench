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
struct rdma_ah_attr {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */

int bnxt_re_modify_ah(struct ib_ah *ib_ah, struct rdma_ah_attr *ah_attr)
{
	return 0;
}