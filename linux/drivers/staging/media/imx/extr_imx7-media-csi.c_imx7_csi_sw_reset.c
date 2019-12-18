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
 int /*<<< orphan*/  imx7_csi_dma_reflash (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_hw_disable (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_hw_enable (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_irq_clear (struct imx7_csi*) ; 
 int /*<<< orphan*/  imx7_csi_rx_fifo_clear (struct imx7_csi*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void imx7_csi_sw_reset(struct imx7_csi *csi)
{
	imx7_csi_hw_disable(csi);

	imx7_csi_rx_fifo_clear(csi);

	imx7_csi_dma_reflash(csi);

	usleep_range(2000, 3000);

	imx7_csi_irq_clear(csi);

	imx7_csi_hw_enable(csi);
}