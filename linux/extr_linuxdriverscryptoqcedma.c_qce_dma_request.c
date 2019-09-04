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
struct qce_dma_data {void* txchan; void* rxchan; scalar_t__ result_buf; scalar_t__ ignore_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ QCE_IGNORE_BUF_SZ ; 
 scalar_t__ QCE_RESULT_BUF_SZ ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 
 void* dma_request_slave_channel_reason (struct device*,char*) ; 
 scalar_t__ kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

int qce_dma_request(struct device *dev, struct qce_dma_data *dma)
{
	int ret;

	dma->txchan = dma_request_slave_channel_reason(dev, "tx");
	if (IS_ERR(dma->txchan))
		return PTR_ERR(dma->txchan);

	dma->rxchan = dma_request_slave_channel_reason(dev, "rx");
	if (IS_ERR(dma->rxchan)) {
		ret = PTR_ERR(dma->rxchan);
		goto error_rx;
	}

	dma->result_buf = kmalloc(QCE_RESULT_BUF_SZ + QCE_IGNORE_BUF_SZ,
				  GFP_KERNEL);
	if (!dma->result_buf) {
		ret = -ENOMEM;
		goto error_nomem;
	}

	dma->ignore_buf = dma->result_buf + QCE_RESULT_BUF_SZ;

	return 0;
error_nomem:
	dma_release_channel(dma->rxchan);
error_rx:
	dma_release_channel(dma->txchan);
	return ret;
}