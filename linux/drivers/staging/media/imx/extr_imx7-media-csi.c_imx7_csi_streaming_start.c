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
struct imx7_csi {int dummy; } ;

/* Variables and functions */
 int imx7_csi_configure (struct imx7_csi*) ; 
 int imx7_csi_dma_start (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_dma_stop (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_enable (struct imx7_csi*) ; 

__attribute__((used)) static int imx7_csi_streaming_start(struct imx7_csi *csi)
{
	int ret;

	ret = imx7_csi_dma_start(csi);
	if (ret < 0)
		return ret;

	ret = imx7_csi_configure(csi);
	if (ret < 0)
		goto dma_stop;

	imx7_csi_enable(csi);

	return 0;

dma_stop:
	imx7_csi_dma_stop(csi);

	return ret;
}