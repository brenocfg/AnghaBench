#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct myrs_hba {int stat_mbox_size; int cmd_mbox_size; int /*<<< orphan*/ * first_cmd_mbox; int /*<<< orphan*/  cmd_mbox_addr; TYPE_1__* pdev; int /*<<< orphan*/ * first_stat_mbox; int /*<<< orphan*/  stat_mbox_addr; int /*<<< orphan*/ * fwstat_buf; int /*<<< orphan*/  fwstat_addr; int /*<<< orphan*/  ctlr_info; int /*<<< orphan*/  event_buf; } ;
struct myrs_fwstat {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrs_unmap(struct myrs_hba *cs)
{
	kfree(cs->event_buf);
	kfree(cs->ctlr_info);
	if (cs->fwstat_buf) {
		dma_free_coherent(&cs->pdev->dev, sizeof(struct myrs_fwstat),
				  cs->fwstat_buf, cs->fwstat_addr);
		cs->fwstat_buf = NULL;
	}
	if (cs->first_stat_mbox) {
		dma_free_coherent(&cs->pdev->dev, cs->stat_mbox_size,
				  cs->first_stat_mbox, cs->stat_mbox_addr);
		cs->first_stat_mbox = NULL;
	}
	if (cs->first_cmd_mbox) {
		dma_free_coherent(&cs->pdev->dev, cs->cmd_mbox_size,
				  cs->first_cmd_mbox, cs->cmd_mbox_addr);
		cs->first_cmd_mbox = NULL;
	}
}