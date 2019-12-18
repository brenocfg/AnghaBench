#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct switchtec_ntb {int link_is_up; TYPE_2__* stdev; int /*<<< orphan*/  ntb; TYPE_1__* peer_shared; TYPE_3__* self_shared; } ;
struct TYPE_6__ {int link_sta; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_MESSAGE ; 
 int /*<<< orphan*/  MSG_CHECK_LINK ; 
 int SWITCHTEC_NTB_MAGIC ; 
 int /*<<< orphan*/  crosslink_init_dbmsgs (struct switchtec_ntb*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 int ioread64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntb_link_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  switchtec_ntb_send_msg (struct switchtec_ntb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  switchtec_ntb_set_link_speed (struct switchtec_ntb*) ; 

__attribute__((used)) static void switchtec_ntb_link_status_update(struct switchtec_ntb *sndev)
{
	int link_sta;
	int old = sndev->link_is_up;

	link_sta = sndev->self_shared->link_sta;
	if (link_sta) {
		u64 peer = ioread64(&sndev->peer_shared->magic);

		if ((peer & 0xFFFFFFFF) == SWITCHTEC_NTB_MAGIC)
			link_sta = peer >> 32;
		else
			link_sta = 0;
	}

	sndev->link_is_up = link_sta;
	switchtec_ntb_set_link_speed(sndev);

	if (link_sta != old) {
		switchtec_ntb_send_msg(sndev, LINK_MESSAGE, MSG_CHECK_LINK);
		ntb_link_event(&sndev->ntb);
		dev_info(&sndev->stdev->dev, "ntb link %s\n",
			 link_sta ? "up" : "down");

		if (link_sta)
			crosslink_init_dbmsgs(sndev);
	}
}