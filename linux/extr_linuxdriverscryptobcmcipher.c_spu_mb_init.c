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
struct mbox_client {int tx_block; int knows_txdone; int /*<<< orphan*/ * tx_done; int /*<<< orphan*/  rx_callback; scalar_t__ tx_tout; struct device* dev; } ;
struct mbox_chan {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int num_chan; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** mbox; TYPE_1__ spu; struct mbox_client mcl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int) ; 
 int /*<<< orphan*/ ** devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ iproc_priv ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbox_request_channel (struct mbox_client*,int) ; 
 int /*<<< orphan*/  spu_rx_callback ; 

__attribute__((used)) static int spu_mb_init(struct device *dev)
{
	struct mbox_client *mcl = &iproc_priv.mcl;
	int err, i;

	iproc_priv.mbox = devm_kcalloc(dev, iproc_priv.spu.num_chan,
				  sizeof(struct mbox_chan *), GFP_KERNEL);
	if (!iproc_priv.mbox)
		return -ENOMEM;

	mcl->dev = dev;
	mcl->tx_block = false;
	mcl->tx_tout = 0;
	mcl->knows_txdone = true;
	mcl->rx_callback = spu_rx_callback;
	mcl->tx_done = NULL;

	for (i = 0; i < iproc_priv.spu.num_chan; i++) {
		iproc_priv.mbox[i] = mbox_request_channel(mcl, i);
		if (IS_ERR(iproc_priv.mbox[i])) {
			err = (int)PTR_ERR(iproc_priv.mbox[i]);
			dev_err(dev,
				"Mbox channel %d request failed with err %d",
				i, err);
			iproc_priv.mbox[i] = NULL;
			goto free_channels;
		}
	}

	return 0;
free_channels:
	for (i = 0; i < iproc_priv.spu.num_chan; i++) {
		if (iproc_priv.mbox[i])
			mbox_free_channel(iproc_priv.mbox[i]);
	}

	return err;
}