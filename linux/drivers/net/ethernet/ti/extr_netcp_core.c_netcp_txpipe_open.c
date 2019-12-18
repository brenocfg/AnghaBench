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
typedef  int /*<<< orphan*/  u8 ;
struct netcp_tx_pipe {int /*<<< orphan*/ * dma_channel; int /*<<< orphan*/ * dma_queue; int /*<<< orphan*/  dma_queue_id; int /*<<< orphan*/  dma_chan_name; TYPE_1__* netcp_device; } ;
struct TYPE_5__ {int filt_einfo; int filt_pswords; int /*<<< orphan*/  priority; } ;
struct TYPE_6__ {TYPE_2__ tx; } ;
struct knav_dma_cfg {TYPE_3__ u; int /*<<< orphan*/  direction; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_4__ {struct device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PRIO_MED_L ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KNAV_QUEUE_SHARED ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ *,...) ; 
 char* dev_name (struct device*) ; 
 int /*<<< orphan*/  knav_dma_close_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * knav_dma_open_channel (struct device*,int /*<<< orphan*/ ,struct knav_dma_cfg*) ; 
 int /*<<< orphan*/ * knav_queue_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct knav_dma_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*) ; 

int netcp_txpipe_open(struct netcp_tx_pipe *tx_pipe)
{
	struct device *dev = tx_pipe->netcp_device->device;
	struct knav_dma_cfg config;
	int ret = 0;
	u8 name[16];

	memset(&config, 0, sizeof(config));
	config.direction = DMA_MEM_TO_DEV;
	config.u.tx.filt_einfo = false;
	config.u.tx.filt_pswords = false;
	config.u.tx.priority = DMA_PRIO_MED_L;

	tx_pipe->dma_channel = knav_dma_open_channel(dev,
				tx_pipe->dma_chan_name, &config);
	if (IS_ERR(tx_pipe->dma_channel)) {
		dev_err(dev, "failed opening tx chan(%s)\n",
			tx_pipe->dma_chan_name);
		ret = PTR_ERR(tx_pipe->dma_channel);
		goto err;
	}

	snprintf(name, sizeof(name), "tx-pipe-%s", dev_name(dev));
	tx_pipe->dma_queue = knav_queue_open(name, tx_pipe->dma_queue_id,
					     KNAV_QUEUE_SHARED);
	if (IS_ERR(tx_pipe->dma_queue)) {
		dev_err(dev, "Could not open DMA queue for channel \"%s\": %d\n",
			name, ret);
		ret = PTR_ERR(tx_pipe->dma_queue);
		goto err;
	}

	dev_dbg(dev, "opened tx pipe %s\n", name);
	return 0;

err:
	if (!IS_ERR_OR_NULL(tx_pipe->dma_channel))
		knav_dma_close_channel(tx_pipe->dma_channel);
	tx_pipe->dma_channel = NULL;
	return ret;
}