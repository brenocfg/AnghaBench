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
struct work_struct {int dummy; } ;
struct amd_ntb_dev {int /*<<< orphan*/  hb_timer; int /*<<< orphan*/  ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_LINK_HB_TIMEOUT ; 
 int /*<<< orphan*/  amd_link_is_up (struct amd_ntb_dev*) ; 
 scalar_t__ amd_poll_link (struct amd_ntb_dev*) ; 
 struct amd_ntb_dev* hb_ndev (struct work_struct*) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void amd_link_hb(struct work_struct *work)
{
	struct amd_ntb_dev *ndev = hb_ndev(work);

	if (amd_poll_link(ndev))
		ntb_link_event(&ndev->ntb);

	if (!amd_link_is_up(ndev))
		schedule_delayed_work(&ndev->hb_timer, AMD_LINK_HB_TIMEOUT);
}