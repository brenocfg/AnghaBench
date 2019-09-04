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
struct hinic_wqs {int /*<<< orphan*/  hwif; } ;
struct hinic_wq {int /*<<< orphan*/  block_idx; int /*<<< orphan*/  page_idx; int /*<<< orphan*/  num_q_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_wq_pages (struct hinic_wq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqs_return_block (struct hinic_wqs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hinic_wq_free(struct hinic_wqs *wqs, struct hinic_wq *wq)
{
	free_wq_pages(wq, wqs->hwif, wq->num_q_pages);

	wqs_return_block(wqs, wq->page_idx, wq->block_idx);
}