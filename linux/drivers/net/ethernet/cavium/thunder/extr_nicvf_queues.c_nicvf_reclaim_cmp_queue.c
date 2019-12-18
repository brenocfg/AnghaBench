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
struct queue_set {int dummy; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NICVF_CQ_RESET ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_CFG ; 
 int /*<<< orphan*/  NIC_QSET_CQ_0_7_CFG2 ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nicvf_reclaim_cmp_queue(struct nicvf *nic,
				    struct queue_set *qs, int qidx)
{
	/* Disable timer threshold (doesn't get reset upon CQ reset */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG2, qidx, 0);
	/* Disable completion queue */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG, qidx, 0);
	/* Reset completion queue */
	nicvf_queue_reg_write(nic, NIC_QSET_CQ_0_7_CFG, qidx, NICVF_CQ_RESET);
}