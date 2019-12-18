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
typedef  unsigned int uint8_t ;
struct spi_transfer {unsigned int* tx_buf; int len; unsigned int* rx_buf; scalar_t__ cs_change; } ;
struct spi_message {int dummy; } ;
struct ad_sigma_delta {unsigned int* data; unsigned int comm; int /*<<< orphan*/  spi; scalar_t__ bus_locked; TYPE_1__* info; } ;
struct TYPE_2__ {unsigned int addr_shift; unsigned int read_mask; scalar_t__ has_registers; } ;

/* Variables and functions */
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 
 int spi_sync_locked (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int ad_sd_read_reg_raw(struct ad_sigma_delta *sigma_delta,
	unsigned int reg, unsigned int size, uint8_t *val)
{
	uint8_t *data = sigma_delta->data;
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = data,
			.len = 1,
		}, {
			.rx_buf = val,
			.len = size,
			.cs_change = sigma_delta->bus_locked,
		},
	};
	struct spi_message m;

	spi_message_init(&m);

	if (sigma_delta->info->has_registers) {
		data[0] = reg << sigma_delta->info->addr_shift;
		data[0] |= sigma_delta->info->read_mask;
		data[0] |= sigma_delta->comm;
		spi_message_add_tail(&t[0], &m);
	}
	spi_message_add_tail(&t[1], &m);

	if (sigma_delta->bus_locked)
		ret = spi_sync_locked(sigma_delta->spi, &m);
	else
		ret = spi_sync(sigma_delta->spi, &m);

	return ret;
}