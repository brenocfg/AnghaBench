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
typedef  int /*<<< orphan*/  uint32_t ;
struct csio_hw {int dummy; } ;
struct csio_fl_dma_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_fwevt_handler (struct csio_hw*) ; 

void
csio_fwevt_intx_handler(struct csio_hw *hw, void *wr, uint32_t len,
			   struct csio_fl_dma_buf *flb, void *priv)
{
	csio_fwevt_handler(hw);
}