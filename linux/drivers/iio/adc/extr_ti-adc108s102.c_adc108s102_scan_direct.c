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
struct adc108s102_state {int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/  scan_single_msg; int /*<<< orphan*/  spi; int /*<<< orphan*/ * tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC108S102_CMD (unsigned int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int spi_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adc108s102_scan_direct(struct adc108s102_state *st, unsigned int ch)
{
	int ret;

	st->tx_buf[0] = cpu_to_be16(ADC108S102_CMD(ch));
	ret = spi_sync(st->spi, &st->scan_single_msg);
	if (ret)
		return ret;

	/* Skip the dummy response in the first slot */
	return be16_to_cpu(st->rx_buf[1]);
}