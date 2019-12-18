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
struct rspi_data {int dummy; } ;

/* Variables and functions */
 unsigned int QSPI_BUFFER_SIZE ; 
 int /*<<< orphan*/  QSPI_SPBFCR ; 
 int /*<<< orphan*/  SPBFCR_RXTRG_1B ; 
 int /*<<< orphan*/  SPBFCR_RXTRG_32B ; 
 int /*<<< orphan*/  SPBFCR_RXTRG_MASK ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qspi_update (struct rspi_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qspi_set_receive_trigger(struct rspi_data *rspi, unsigned int len)
{
	unsigned int n;

	n = min(len, QSPI_BUFFER_SIZE);

	if (len >= QSPI_BUFFER_SIZE) {
		/* sets triggering number to 32 bytes */
		qspi_update(rspi, SPBFCR_RXTRG_MASK,
			     SPBFCR_RXTRG_32B, QSPI_SPBFCR);
	} else {
		/* sets triggering number to 1 byte */
		qspi_update(rspi, SPBFCR_RXTRG_MASK,
			     SPBFCR_RXTRG_1B, QSPI_SPBFCR);
	}
	return n;
}