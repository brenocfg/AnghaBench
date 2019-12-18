#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct switchtec_ntb {TYPE_2__* self_shared; TYPE_1__* stdev; } ;
struct ntb_dev {int dummy; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
struct TYPE_4__ {int link_sta; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_MESSAGE ; 
 int /*<<< orphan*/  MSG_LINK_UP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 
 int /*<<< orphan*/  switchtec_ntb_link_status_update (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  switchtec_ntb_send_msg (struct switchtec_ntb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int switchtec_ntb_link_enable(struct ntb_dev *ntb,
				     enum ntb_speed max_speed,
				     enum ntb_width max_width)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	dev_dbg(&sndev->stdev->dev, "enabling link\n");

	sndev->self_shared->link_sta = 1;
	switchtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_LINK_UP);

	switchtec_ntb_link_status_update(sndev);

	return 0;
}