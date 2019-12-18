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
struct mpc8xxx_spi {int flags; TYPE_1__* pram; int /*<<< orphan*/  subblock; } ;
struct TYPE_2__ {int /*<<< orphan*/  tbase; int /*<<< orphan*/  tbptr; int /*<<< orphan*/  tstate; int /*<<< orphan*/  rbase; int /*<<< orphan*/  rbptr; int /*<<< orphan*/  rstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPM_CR_INIT_TRX ; 
 int /*<<< orphan*/  CPM_SPI_CMD ; 
 int /*<<< orphan*/  QE_CR_PROTOCOL_UNSPECIFIED ; 
 int /*<<< orphan*/  QE_INIT_TX_RX ; 
 int SPI_CPM1 ; 
 int SPI_QE ; 
 int /*<<< orphan*/  cpm_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_be16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fsl_spi_cpm_reinit_txrx(struct mpc8xxx_spi *mspi)
{
	if (mspi->flags & SPI_QE) {
		qe_issue_cmd(QE_INIT_TX_RX, mspi->subblock,
			     QE_CR_PROTOCOL_UNSPECIFIED, 0);
	} else {
		if (mspi->flags & SPI_CPM1) {
			out_be32(&mspi->pram->rstate, 0);
			out_be16(&mspi->pram->rbptr,
				 in_be16(&mspi->pram->rbase));
			out_be32(&mspi->pram->tstate, 0);
			out_be16(&mspi->pram->tbptr,
				 in_be16(&mspi->pram->tbase));
		} else {
			cpm_command(CPM_SPI_CMD, CPM_CR_INIT_TRX);
		}
	}
}