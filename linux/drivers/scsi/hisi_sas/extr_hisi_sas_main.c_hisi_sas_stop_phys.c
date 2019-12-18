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
struct hisi_hba {int n_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_phy_enable (struct hisi_hba*,int,int /*<<< orphan*/ ) ; 

void hisi_sas_stop_phys(struct hisi_hba *hisi_hba)
{
	int phy_no;

	for (phy_no = 0; phy_no < hisi_hba->n_phy; phy_no++)
		hisi_sas_phy_enable(hisi_hba, phy_no, 0);
}