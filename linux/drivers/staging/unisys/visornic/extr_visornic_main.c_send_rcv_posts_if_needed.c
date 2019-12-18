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
struct TYPE_2__ {int /*<<< orphan*/  extra_rcvbufs_sent; } ;
struct visornic_devdata {int num_rcv_bufs_could_not_alloc; int num_rcv_bufs; TYPE_1__ chstat; int /*<<< orphan*/ ** rcvbuf; int /*<<< orphan*/  alloc_failed_in_if_needed_cnt; struct net_device* netdev; scalar_t__ enab_dis_acked; scalar_t__ enabled; struct uiscmdrsp* cmdrsp_rcv; } ;
struct uiscmdrsp {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * alloc_rcv_buf (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int post_skb (struct uiscmdrsp*,struct visornic_devdata*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_rcv_posts_if_needed(struct visornic_devdata *devdata)
{
	int i;
	struct net_device *netdev;
	struct uiscmdrsp *cmdrsp = devdata->cmdrsp_rcv;
	int cur_num_rcv_bufs_to_alloc, rcv_bufs_allocated;
	int err;

	/* don't do this until vnic is marked ready */
	if (!(devdata->enabled && devdata->enab_dis_acked))
		return;

	netdev = devdata->netdev;
	rcv_bufs_allocated = 0;
	/* this code is trying to prevent getting stuck here forever,
	 * but still retry it if you cant allocate them all this time.
	 */
	cur_num_rcv_bufs_to_alloc = devdata->num_rcv_bufs_could_not_alloc;
	while (cur_num_rcv_bufs_to_alloc > 0) {
		cur_num_rcv_bufs_to_alloc--;
		for (i = 0; i < devdata->num_rcv_bufs; i++) {
			if (devdata->rcvbuf[i])
				continue;
			devdata->rcvbuf[i] = alloc_rcv_buf(netdev);
			if (!devdata->rcvbuf[i]) {
				devdata->alloc_failed_in_if_needed_cnt++;
				break;
			}
			rcv_bufs_allocated++;
			err = post_skb(cmdrsp, devdata, devdata->rcvbuf[i]);
			if (err) {
				kfree_skb(devdata->rcvbuf[i]);
				devdata->rcvbuf[i] = NULL;
				break;
			}
			devdata->chstat.extra_rcvbufs_sent++;
		}
	}
	devdata->num_rcv_bufs_could_not_alloc -= rcv_bufs_allocated;
}