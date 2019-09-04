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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct pdc_state {int /*<<< orphan*/  rx_buf_pool; int /*<<< orphan*/  pdc_resp_hdr_len; scalar_t__ use_bcm_hdr; int /*<<< orphan*/  rx_status_len; struct platform_device* pdev; } ;

/* Variables and functions */
 scalar_t__ BCM_HDR_LEN ; 
 int ENOMEM ; 
 int PDC_SUCCESS ; 
 int /*<<< orphan*/  RX_BUF_ALIGN ; 
 int /*<<< orphan*/  dma_pool_create (char*,struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pdc_rx_buf_pool_create(struct pdc_state *pdcs)
{
	struct platform_device *pdev;
	struct device *dev;

	pdev = pdcs->pdev;
	dev = &pdev->dev;

	pdcs->pdc_resp_hdr_len = pdcs->rx_status_len;
	if (pdcs->use_bcm_hdr)
		pdcs->pdc_resp_hdr_len += BCM_HDR_LEN;

	pdcs->rx_buf_pool = dma_pool_create("pdc rx bufs", dev,
					    pdcs->pdc_resp_hdr_len,
					    RX_BUF_ALIGN, 0);
	if (!pdcs->rx_buf_pool)
		return -ENOMEM;

	return PDC_SUCCESS;
}