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
typedef  int /*<<< orphan*/  u16 ;
struct hinic_wq {int /*<<< orphan*/  wqebb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASKED_WQE_IDX (struct hinic_wq*,int /*<<< orphan*/ ) ; 
 int WQE_PAGE_OFF (struct hinic_wq*,int /*<<< orphan*/ ) ; 
 void* WQ_PAGE_ADDR (struct hinic_wq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_wqe_to_shadow(struct hinic_wq *wq, void *shadow_addr,
			       int num_wqebbs, u16 idx)
{
	void *wqebb_addr;
	int i;

	for (i = 0; i < num_wqebbs; i++, idx++) {
		idx = MASKED_WQE_IDX(wq, idx);
		wqebb_addr = WQ_PAGE_ADDR(wq, idx) +
			     WQE_PAGE_OFF(wq, idx);

		memcpy(shadow_addr, wqebb_addr, wq->wqebb_size);

		shadow_addr += wq->wqebb_size;
	}
}