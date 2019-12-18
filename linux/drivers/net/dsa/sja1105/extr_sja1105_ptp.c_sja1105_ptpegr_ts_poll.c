#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct sja1105_regs {int /*<<< orphan*/ * ptpegr_ts; } ;
struct sja1105_private {TYPE_1__* info; } ;
struct TYPE_2__ {int ptp_ts_bits; int /*<<< orphan*/  ptpegr_ts_bytes; struct sja1105_regs* regs; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SPI_READ ; 
 int sja1105_spi_send_packed_buf (struct sja1105_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sja1105_unpack (int /*<<< orphan*/ *,scalar_t__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int sja1105_ptpegr_ts_poll(struct sja1105_private *priv, int port, u64 *ts)
{
	const struct sja1105_regs *regs = priv->info->regs;
	int tstamp_bit_start, tstamp_bit_end;
	int timeout = 10;
	u8 packed_buf[8];
	u64 update;
	int rc;

	do {
		rc = sja1105_spi_send_packed_buf(priv, SPI_READ,
						 regs->ptpegr_ts[port],
						 packed_buf,
						 priv->info->ptpegr_ts_bytes);
		if (rc < 0)
			return rc;

		sja1105_unpack(packed_buf, &update, 0, 0,
			       priv->info->ptpegr_ts_bytes);
		if (update)
			break;

		usleep_range(10, 50);
	} while (--timeout);

	if (!timeout)
		return -ETIMEDOUT;

	/* Point the end bit to the second 32-bit word on P/Q/R/S,
	 * no-op on E/T.
	 */
	tstamp_bit_end = (priv->info->ptpegr_ts_bytes - 4) * 8;
	/* Shift the 24-bit timestamp on E/T to be collected from 31:8.
	 * No-op on P/Q/R/S.
	 */
	tstamp_bit_end += 32 - priv->info->ptp_ts_bits;
	tstamp_bit_start = tstamp_bit_end + priv->info->ptp_ts_bits - 1;

	*ts = 0;

	sja1105_unpack(packed_buf, ts, tstamp_bit_start, tstamp_bit_end,
		       priv->info->ptpegr_ts_bytes);

	return 0;
}