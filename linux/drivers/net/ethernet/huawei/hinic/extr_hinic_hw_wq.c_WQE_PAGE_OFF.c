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
struct hinic_wq {int num_wqebbs_per_page; int wqebb_size_shift; } ;
typedef  int idx ;

/* Variables and functions */

__attribute__((used)) static inline int WQE_PAGE_OFF(struct hinic_wq *wq, u16 idx)
{
	return (((idx) & ((wq)->num_wqebbs_per_page - 1))
		<< (wq)->wqebb_size_shift);
}