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
struct lpfc_vport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_disc_flush_list (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_flush_cmd (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_flush_rscn (struct lpfc_vport*) ; 

void
lpfc_cleanup_discovery_resources(struct lpfc_vport *vport)
{
	lpfc_els_flush_rscn(vport);
	lpfc_els_flush_cmd(vport);
	lpfc_disc_flush_list(vport);
}