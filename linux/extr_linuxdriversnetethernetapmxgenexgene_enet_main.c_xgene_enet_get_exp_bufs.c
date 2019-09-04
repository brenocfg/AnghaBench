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
struct xgene_enet_desc_ring {size_t exp_buf_tail; int slots; int /*<<< orphan*/ * exp_bufs; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 size_t MAX_EXP_BUFFS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __le64 *xgene_enet_get_exp_bufs(struct xgene_enet_desc_ring *ring)
{
	__le64 *exp_bufs;

	exp_bufs = &ring->exp_bufs[ring->exp_buf_tail * MAX_EXP_BUFFS];
	memset(exp_bufs, 0, sizeof(__le64) * MAX_EXP_BUFFS);
	ring->exp_buf_tail = (ring->exp_buf_tail + 1) & ((ring->slots / 2) - 1);

	return exp_bufs;
}