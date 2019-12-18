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
typedef  int /*<<< orphan*/  u8 ;
struct falcon_spi_device {int dummy; } ;
struct ef4_nic {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  FALCON_SPI_MAX_LEN ; 
 int /*<<< orphan*/  SPI_READ ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int falcon_spi_cmd (struct ef4_nic*,struct falcon_spi_device const*,unsigned int,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 unsigned int falcon_spi_munge_command (struct falcon_spi_device const*,int /*<<< orphan*/ ,scalar_t__) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
falcon_spi_read(struct ef4_nic *efx, const struct falcon_spi_device *spi,
		loff_t start, size_t len, size_t *retlen, u8 *buffer)
{
	size_t block_len, pos = 0;
	unsigned int command;
	int rc = 0;

	while (pos < len) {
		block_len = min(len - pos, FALCON_SPI_MAX_LEN);

		command = falcon_spi_munge_command(spi, SPI_READ, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos, NULL,
				    buffer + pos, block_len);
		if (rc)
			break;
		pos += block_len;

		/* Avoid locking up the system */
		cond_resched();
		if (signal_pending(current)) {
			rc = -EINTR;
			break;
		}
	}

	if (retlen)
		*retlen = pos;
	return rc;
}