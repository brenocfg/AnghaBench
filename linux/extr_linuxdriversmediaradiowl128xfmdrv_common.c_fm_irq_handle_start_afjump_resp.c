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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stage; } ;
struct fmdev {int /*<<< orphan*/  flag; TYPE_1__ irq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_AF_SWITCH_INPROGRESS ; 
 int /*<<< orphan*/  FM_INTTASK_RUNNING ; 
 int /*<<< orphan*/  FM_SEND_FLAG_GETCMD_IDX ; 
 scalar_t__ check_cmdresp_status (struct fmdev*,struct sk_buff**) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm_irq_handle_start_afjump_resp(struct fmdev *fmdev)
{
	struct sk_buff *skb;

	if (check_cmdresp_status(fmdev, &skb))
		return;

	fmdev->irq_info.stage = FM_SEND_FLAG_GETCMD_IDX;
	set_bit(FM_AF_SWITCH_INPROGRESS, &fmdev->flag);
	clear_bit(FM_INTTASK_RUNNING, &fmdev->flag);
}