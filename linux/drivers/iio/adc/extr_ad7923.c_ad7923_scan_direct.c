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
struct ad7923_state {int settings; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  spi; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int AD7923_CHANNEL_WRITE (unsigned int) ; 
 int /*<<< orphan*/  AD7923_SEQUENCE_OFF ; 
 int AD7923_SEQUENCE_WRITE (int /*<<< orphan*/ ) ; 
 int AD7923_SHIFT_REGISTER ; 
 int AD7923_WRITE_CR ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7923_scan_direct(struct ad7923_state *st, unsigned ch)
{
	int ret, cmd;

	cmd = AD7923_WRITE_CR | AD7923_CHANNEL_WRITE(ch) |
		AD7923_SEQUENCE_WRITE(AD7923_SEQUENCE_OFF) |
		st->settings;
	cmd <<= AD7923_SHIFT_REGISTER;
	st->tx_buf[0] = cpu_to_be16(cmd);

	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		return ret;

	return be16_to_cpu(st->rx_buf[0]);
}