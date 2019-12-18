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
struct hinic_wq {int wqebbs_per_page_shift; int num_q_pages; } ;

/* Variables and functions */

__attribute__((used)) static inline int WQE_PAGE_NUM(struct hinic_wq *wq, u16 idx)
{
	return (((idx) >> ((wq)->wqebbs_per_page_shift))
		& ((wq)->num_q_pages - 1));
}