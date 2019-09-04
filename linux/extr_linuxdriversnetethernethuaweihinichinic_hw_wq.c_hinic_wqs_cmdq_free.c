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
struct hinic_wq {int /*<<< orphan*/  num_q_pages; } ;
struct hinic_cmdq_pages {int /*<<< orphan*/  hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmdq_free_page (struct hinic_cmdq_pages*) ; 
 int /*<<< orphan*/  free_wq_pages (struct hinic_wq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hinic_wqs_cmdq_free(struct hinic_cmdq_pages *cmdq_pages,
			 struct hinic_wq *wq, int cmdq_blocks)
{
	int i;

	for (i = 0; i < cmdq_blocks; i++)
		free_wq_pages(&wq[i], cmdq_pages->hwif, wq[i].num_q_pages);

	cmdq_free_page(cmdq_pages);
}