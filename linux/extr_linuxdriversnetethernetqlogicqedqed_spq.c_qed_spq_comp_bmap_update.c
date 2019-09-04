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
typedef  int u16 ;
struct qed_spq {int /*<<< orphan*/  chain; int /*<<< orphan*/  comp_bitmap_idx; int /*<<< orphan*/  p_comp_bitmap; } ;
struct qed_hwfn {struct qed_spq* p_spq; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int SPQ_RING_SIZE ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_return_produced (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_spq_comp_bmap_update(struct qed_hwfn *p_hwfn, __le16 echo)
{
	u16 pos = le16_to_cpu(echo) % SPQ_RING_SIZE;
	struct qed_spq *p_spq = p_hwfn->p_spq;

	__set_bit(pos, p_spq->p_comp_bitmap);
	while (test_bit(p_spq->comp_bitmap_idx,
			p_spq->p_comp_bitmap)) {
		__clear_bit(p_spq->comp_bitmap_idx,
			    p_spq->p_comp_bitmap);
		p_spq->comp_bitmap_idx++;
		qed_chain_return_produced(&p_spq->chain);
	}
}