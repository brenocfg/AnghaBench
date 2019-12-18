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
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_enable_la (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_linkdown (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_unregister_unused_fcf (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_mbx_issue_link_down(struct lpfc_hba *phba)
{
	lpfc_linkdown(phba);
	lpfc_enable_la(phba);
	lpfc_unregister_unused_fcf(phba);
	/* turn on Link Attention interrupts - no CLEAR_LA needed */
}