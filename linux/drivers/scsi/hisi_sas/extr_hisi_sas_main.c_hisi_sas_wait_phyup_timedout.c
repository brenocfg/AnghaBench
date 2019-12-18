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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int id; } ;
struct hisi_sas_phy {TYPE_1__ sas_phy; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_PHYE_LINK_RESET ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct hisi_sas_phy* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_notify_phy_event (struct hisi_sas_phy*,int /*<<< orphan*/ ) ; 
 struct hisi_sas_phy* phy ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void hisi_sas_wait_phyup_timedout(struct timer_list *t)
{
	struct hisi_sas_phy *phy = from_timer(phy, t, timer);
	struct hisi_hba *hisi_hba = phy->hisi_hba;
	struct device *dev = hisi_hba->dev;
	int phy_no = phy->sas_phy.id;

	dev_warn(dev, "phy%d wait phyup timeout, issuing link reset\n", phy_no);
	hisi_sas_notify_phy_event(phy, HISI_PHYE_LINK_RESET);
}