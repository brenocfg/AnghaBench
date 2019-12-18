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
typedef  int u8 ;
struct enc28j60_net {int bank; } ;

/* Variables and functions */
 int BANK_MASK ; 
 int ECON1 ; 
 int ECON1_BSEL0 ; 
 int ECON1_BSEL1 ; 
 int EIE ; 
 int /*<<< orphan*/  ENC28J60_BIT_FIELD_CLR ; 
 int /*<<< orphan*/  ENC28J60_BIT_FIELD_SET ; 
 int /*<<< orphan*/  spi_write_op (struct enc28j60_net*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void enc28j60_set_bank(struct enc28j60_net *priv, u8 addr)
{
	u8 b = (addr & BANK_MASK) >> 5;

	/* These registers (EIE, EIR, ESTAT, ECON2, ECON1)
	 * are present in all banks, no need to switch bank.
	 */
	if (addr >= EIE && addr <= ECON1)
		return;

	/* Clear or set each bank selection bit as needed */
	if ((b & ECON1_BSEL0) != (priv->bank & ECON1_BSEL0)) {
		if (b & ECON1_BSEL0)
			spi_write_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL0);
		else
			spi_write_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL0);
	}
	if ((b & ECON1_BSEL1) != (priv->bank & ECON1_BSEL1)) {
		if (b & ECON1_BSEL1)
			spi_write_op(priv, ENC28J60_BIT_FIELD_SET, ECON1,
					ECON1_BSEL1);
		else
			spi_write_op(priv, ENC28J60_BIT_FIELD_CLR, ECON1,
					ECON1_BSEL1);
	}
	priv->bank = b;
}