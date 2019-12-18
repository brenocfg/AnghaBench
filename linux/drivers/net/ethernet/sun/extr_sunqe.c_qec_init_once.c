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
typedef  int u8 ;
struct sunqec {int qec_bursts; scalar_t__ gregs; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int DMA_BURST32 ; 
 int DMA_BURST64 ; 
 scalar_t__ GLOB_CTRL ; 
 int GLOB_CTRL_B16 ; 
 int GLOB_CTRL_B32 ; 
 int GLOB_CTRL_B64 ; 
 scalar_t__ GLOB_MSIZE ; 
 scalar_t__ GLOB_PSIZE ; 
 int GLOB_PSIZE_2048 ; 
 scalar_t__ GLOB_RSIZE ; 
 scalar_t__ GLOB_TSIZE ; 
 int resource_size (int /*<<< orphan*/ *) ; 
 scalar_t__ sbus_can_burst64 () ; 
 int /*<<< orphan*/  sbus_writel (int,scalar_t__) ; 

__attribute__((used)) static void qec_init_once(struct sunqec *qecp, struct platform_device *op)
{
	u8 bsizes = qecp->qec_bursts;

	if (sbus_can_burst64() && (bsizes & DMA_BURST64)) {
		sbus_writel(GLOB_CTRL_B64, qecp->gregs + GLOB_CTRL);
	} else if (bsizes & DMA_BURST32) {
		sbus_writel(GLOB_CTRL_B32, qecp->gregs + GLOB_CTRL);
	} else {
		sbus_writel(GLOB_CTRL_B16, qecp->gregs + GLOB_CTRL);
	}

	/* Packetsize only used in 100baseT BigMAC configurations,
	 * set it to zero just to be on the safe side.
	 */
	sbus_writel(GLOB_PSIZE_2048, qecp->gregs + GLOB_PSIZE);

	/* Set the local memsize register, divided up to one piece per QE channel. */
	sbus_writel((resource_size(&op->resource[1]) >> 2),
		    qecp->gregs + GLOB_MSIZE);

	/* Divide up the local QEC memory amongst the 4 QE receiver and
	 * transmitter FIFOs.  Basically it is (total / 2 / num_channels).
	 */
	sbus_writel((resource_size(&op->resource[1]) >> 2) >> 1,
		    qecp->gregs + GLOB_TSIZE);
	sbus_writel((resource_size(&op->resource[1]) >> 2) >> 1,
		    qecp->gregs + GLOB_RSIZE);
}