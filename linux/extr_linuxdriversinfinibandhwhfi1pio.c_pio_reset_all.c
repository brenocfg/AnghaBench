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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SEND_PIO_ERR_CLEAR ; 
 int /*<<< orphan*/  SEND_PIO_ERR_CLEAR_PIO_INIT_SM_IN_ERR_SMASK ; 
 int /*<<< orphan*/  SEND_PIO_INIT_CTXT ; 
 int /*<<< orphan*/  SEND_PIO_INIT_CTXT_PIO_ALL_CTXT_INIT_SMASK ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,char*) ; 
 int pio_init_wait_progress (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pio_reset_all(struct hfi1_devdata *dd)
{
	int ret;

	/* make sure the init engine is not busy */
	ret = pio_init_wait_progress(dd);
	/* ignore any timeout */
	if (ret == -EIO) {
		/* clear the error */
		write_csr(dd, SEND_PIO_ERR_CLEAR,
			  SEND_PIO_ERR_CLEAR_PIO_INIT_SM_IN_ERR_SMASK);
	}

	/* reset init all */
	write_csr(dd, SEND_PIO_INIT_CTXT,
		  SEND_PIO_INIT_CTXT_PIO_ALL_CTXT_INIT_SMASK);
	udelay(2);
	ret = pio_init_wait_progress(dd);
	if (ret < 0) {
		dd_dev_err(dd,
			   "PIO send context init %s while initializing all PIO blocks\n",
			   ret == -ETIMEDOUT ? "is stuck" : "had an error");
	}
}