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
struct fintek_8250 {int pid; } ;

/* Variables and functions */
#define  CHIP_ID_F81216H 129 
#define  CHIP_ID_F81866 128 
 int /*<<< orphan*/  FIFO_CTRL ; 
 int FIFO_MODE_128 ; 
 int FIFO_MODE_MASK ; 
 int RXFTHR_MODE_4X ; 
 int RXFTHR_MODE_MASK ; 
 int /*<<< orphan*/  sio_write_mask_reg (struct fintek_8250*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fintek_8250_set_max_fifo(struct fintek_8250 *pdata)
{
	switch (pdata->pid) {
	case CHIP_ID_F81216H: /* 128Bytes FIFO */
	case CHIP_ID_F81866:
		sio_write_mask_reg(pdata, FIFO_CTRL,
				   FIFO_MODE_MASK | RXFTHR_MODE_MASK,
				   FIFO_MODE_128 | RXFTHR_MODE_4X);
		break;

	default: /* Default 16Bytes FIFO */
		break;
	}
}