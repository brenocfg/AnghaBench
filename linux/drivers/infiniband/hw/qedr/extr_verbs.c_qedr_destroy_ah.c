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
struct qedr_ah {int /*<<< orphan*/  attr; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 struct qedr_ah* get_qedr_ah (struct ib_ah*) ; 
 int /*<<< orphan*/  rdma_destroy_ah_attr (int /*<<< orphan*/ *) ; 

void qedr_destroy_ah(struct ib_ah *ibah, u32 flags)
{
	struct qedr_ah *ah = get_qedr_ah(ibah);

	rdma_destroy_ah_attr(&ah->attr);
}