#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct bcm_qspi {int bspi_rf_op_len; size_t bspi_rf_op_idx; TYPE_4__* bspi_rf_op; TYPE_1__* pdev; } ;
struct TYPE_6__ {scalar_t__ in; } ;
struct TYPE_7__ {TYPE_2__ buf; } ;
struct TYPE_8__ {TYPE_3__ data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ALIGNED (uintptr_t,int) ; 
 int /*<<< orphan*/  bcm_qspi_bspi_lr_is_fifo_empty (struct bcm_qspi*) ; 
 int bcm_qspi_bspi_lr_read_fifo (struct bcm_qspi*) ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,TYPE_4__*,scalar_t__,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static void bcm_qspi_bspi_lr_data_read(struct bcm_qspi *qspi)
{
	u32 *buf = (u32 *)qspi->bspi_rf_op->data.buf.in;
	u32 data = 0;

	dev_dbg(&qspi->pdev->dev, "xfer %p rx %p rxlen %d\n", qspi->bspi_rf_op,
		qspi->bspi_rf_op->data.buf.in, qspi->bspi_rf_op_len);
	while (!bcm_qspi_bspi_lr_is_fifo_empty(qspi)) {
		data = bcm_qspi_bspi_lr_read_fifo(qspi);
		if (likely(qspi->bspi_rf_op_len >= 4) &&
		    IS_ALIGNED((uintptr_t)buf, 4)) {
			buf[qspi->bspi_rf_op_idx++] = data;
			qspi->bspi_rf_op_len -= 4;
		} else {
			/* Read out remaining bytes, make sure*/
			u8 *cbuf = (u8 *)&buf[qspi->bspi_rf_op_idx];

			data = cpu_to_le32(data);
			while (qspi->bspi_rf_op_len) {
				*cbuf++ = (u8)data;
				data >>= 8;
				qspi->bspi_rf_op_len--;
			}
		}
	}
}