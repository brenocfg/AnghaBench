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
struct geni_se {int dummy; } ;
typedef  enum geni_se_xfer_mode { ____Placeholder_geni_se_xfer_mode } geni_se_xfer_mode ;

/* Variables and functions */
#define  GENI_SE_DMA 130 
#define  GENI_SE_FIFO 129 
#define  GENI_SE_INVALID 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  geni_se_select_dma_mode (struct geni_se*) ; 
 int /*<<< orphan*/  geni_se_select_fifo_mode (struct geni_se*) ; 

void geni_se_select_mode(struct geni_se *se, enum geni_se_xfer_mode mode)
{
	WARN_ON(mode != GENI_SE_FIFO && mode != GENI_SE_DMA);

	switch (mode) {
	case GENI_SE_FIFO:
		geni_se_select_fifo_mode(se);
		break;
	case GENI_SE_DMA:
		geni_se_select_dma_mode(se);
		break;
	case GENI_SE_INVALID:
	default:
		break;
	}
}