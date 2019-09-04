#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  head_mask; int /*<<< orphan*/  len_ena_mask; int /*<<< orphan*/  len_mask; int /*<<< orphan*/  bal; int /*<<< orphan*/  bah; int /*<<< orphan*/  len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct TYPE_3__ {int /*<<< orphan*/  head_mask; int /*<<< orphan*/  len_ena_mask; int /*<<< orphan*/  len_mask; int /*<<< orphan*/  bal; int /*<<< orphan*/  bah; int /*<<< orphan*/  len; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct ice_ctl_q_info {TYPE_2__ rq; TYPE_1__ sq; } ;
struct ice_hw {struct ice_ctl_q_info adminq; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_FW_ARQBAH ; 
 int /*<<< orphan*/  PF_FW_ARQBAL ; 
 int /*<<< orphan*/  PF_FW_ARQH ; 
 int /*<<< orphan*/  PF_FW_ARQH_ARQH_M ; 
 int /*<<< orphan*/  PF_FW_ARQLEN ; 
 int /*<<< orphan*/  PF_FW_ARQLEN_ARQENABLE_M ; 
 int /*<<< orphan*/  PF_FW_ARQLEN_ARQLEN_M ; 
 int /*<<< orphan*/  PF_FW_ARQT ; 
 int /*<<< orphan*/  PF_FW_ATQBAH ; 
 int /*<<< orphan*/  PF_FW_ATQBAL ; 
 int /*<<< orphan*/  PF_FW_ATQH ; 
 int /*<<< orphan*/  PF_FW_ATQH_ATQH_M ; 
 int /*<<< orphan*/  PF_FW_ATQLEN ; 
 int /*<<< orphan*/  PF_FW_ATQLEN_ATQENABLE_M ; 
 int /*<<< orphan*/  PF_FW_ATQLEN_ATQLEN_M ; 
 int /*<<< orphan*/  PF_FW_ATQT ; 

__attribute__((used)) static void ice_adminq_init_regs(struct ice_hw *hw)
{
	struct ice_ctl_q_info *cq = &hw->adminq;

	cq->sq.head = PF_FW_ATQH;
	cq->sq.tail = PF_FW_ATQT;
	cq->sq.len = PF_FW_ATQLEN;
	cq->sq.bah = PF_FW_ATQBAH;
	cq->sq.bal = PF_FW_ATQBAL;
	cq->sq.len_mask = PF_FW_ATQLEN_ATQLEN_M;
	cq->sq.len_ena_mask = PF_FW_ATQLEN_ATQENABLE_M;
	cq->sq.head_mask = PF_FW_ATQH_ATQH_M;

	cq->rq.head = PF_FW_ARQH;
	cq->rq.tail = PF_FW_ARQT;
	cq->rq.len = PF_FW_ARQLEN;
	cq->rq.bah = PF_FW_ARQBAH;
	cq->rq.bal = PF_FW_ARQBAL;
	cq->rq.len_mask = PF_FW_ARQLEN_ARQLEN_M;
	cq->rq.len_ena_mask = PF_FW_ARQLEN_ARQENABLE_M;
	cq->rq.head_mask = PF_FW_ARQH_ARQH_M;
}