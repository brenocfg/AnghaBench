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
 int /*<<< orphan*/  RSPI_SPBFCR ; 
 int SPBFCR_RXRST ; 
 int SPBFCR_TXRST ; 
 int /*<<< orphan*/  rspi_receive_init (struct rspi_data const*) ; 
 int /*<<< orphan*/  rspi_write8 (struct rspi_data const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rspi_rz_receive_init(const struct rspi_data *rspi)
{
	rspi_receive_init(rspi);
	rspi_write8(rspi, SPBFCR_TXRST | SPBFCR_RXRST, RSPI_SPBFCR);
	rspi_write8(rspi, 0, RSPI_SPBFCR);
}