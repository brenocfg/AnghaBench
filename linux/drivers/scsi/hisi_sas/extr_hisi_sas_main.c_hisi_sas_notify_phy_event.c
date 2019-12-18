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
struct hisi_sas_phy {int /*<<< orphan*/ * works; struct hisi_hba* hisi_hba; } ;
struct hisi_hba {int /*<<< orphan*/  wq; } ;
typedef  enum hisi_sas_phy_event { ____Placeholder_hisi_sas_phy_event } hisi_sas_phy_event ;

/* Variables and functions */
 int HISI_PHYES_NUM ; 
 scalar_t__ WARN_ON (int) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool hisi_sas_notify_phy_event(struct hisi_sas_phy *phy,
				enum hisi_sas_phy_event event)
{
	struct hisi_hba *hisi_hba = phy->hisi_hba;

	if (WARN_ON(event >= HISI_PHYES_NUM))
		return false;

	return queue_work(hisi_hba->wq, &phy->works[event]);
}