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
struct st_proto_s {int chnl_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_queue; } ;
struct TYPE_4__ {scalar_t__ freq; TYPE_1__ rds; } ;
struct fmdev {int /*<<< orphan*/  flag; TYPE_2__ rx; int /*<<< orphan*/ * resp_comp; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  rx_task; int /*<<< orphan*/  tx_task; } ;
typedef  int /*<<< orphan*/  fm_st_proto ;

/* Variables and functions */
 int /*<<< orphan*/  FM_CORE_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmdbg (char*) ; 
 int /*<<< orphan*/  fmerr (char*,int) ; 
 int /*<<< orphan*/  memset (struct st_proto_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int st_unregister (struct st_proto_s*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int fmc_release(struct fmdev *fmdev)
{
	static struct st_proto_s fm_st_proto;
	int ret;

	if (!test_bit(FM_CORE_READY, &fmdev->flag)) {
		fmdbg("FM Core is already down\n");
		return 0;
	}
	/* Service pending read */
	wake_up_interruptible(&fmdev->rx.rds.read_queue);

	tasklet_kill(&fmdev->tx_task);
	tasklet_kill(&fmdev->rx_task);

	skb_queue_purge(&fmdev->tx_q);
	skb_queue_purge(&fmdev->rx_q);

	fmdev->resp_comp = NULL;
	fmdev->rx.freq = 0;

	memset(&fm_st_proto, 0, sizeof(fm_st_proto));
	fm_st_proto.chnl_id = 0x08;

	ret = st_unregister(&fm_st_proto);

	if (ret < 0)
		fmerr("Failed to de-register FM from ST %d\n", ret);
	else
		fmdbg("Successfully unregistered from ST\n");

	clear_bit(FM_CORE_READY, &fmdev->flag);
	return ret;
}