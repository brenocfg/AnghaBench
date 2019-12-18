#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; } ;
struct hisi_sas_phy {TYPE_1__ timer; } ;
struct hisi_hba {struct device* dev; struct hisi_sas_phy* phy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int HISI_SAS_WAIT_PHYUP_TIMEOUT ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void hisi_sas_phy_oob_ready(struct hisi_hba *hisi_hba, int phy_no)
{
	struct hisi_sas_phy *phy = &hisi_hba->phy[phy_no];
	struct device *dev = hisi_hba->dev;

	if (!timer_pending(&phy->timer)) {
		dev_dbg(dev, "phy%d OOB ready\n", phy_no);
		phy->timer.expires = jiffies + HISI_SAS_WAIT_PHYUP_TIMEOUT * HZ;
		add_timer(&phy->timer);
	}
}