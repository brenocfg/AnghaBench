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
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_6__ {int nbytes; } ;
struct TYPE_5__ {int buswidth; } ;
struct spi_mem_op {TYPE_4__ cmd; TYPE_2__ addr; TYPE_1__ data; } ;
struct bcm_qspi {TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSPI ; 
 int BSPI_ADDRLEN_4BYTES ; 
 int /*<<< orphan*/  BSPI_STRAP_OVERRIDE_CTRL ; 
 int BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE ; 
 int BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL ; 
 int BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD ; 
 int BSPI_STRAP_OVERRIDE_CTRL_OVERRIDE ; 
 int EINVAL ; 
#define  SPI_NBITS_DUAL 130 
#define  SPI_NBITS_QUAD 129 
#define  SPI_NBITS_SINGLE 128 
 int /*<<< orphan*/  bcm_qspi_bspi_set_xfer_params (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int,int) ; 

__attribute__((used)) static int bcm_qspi_bspi_set_override(struct bcm_qspi *qspi,
				      const struct spi_mem_op *op, int hp)
{
	int width = op->data.buswidth ? op->data.buswidth : SPI_NBITS_SINGLE;
	int addrlen = op->addr.nbytes;
	u32 data = bcm_qspi_read(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL);

	dev_dbg(&qspi->pdev->dev, "set override mode w %x addrlen %x hp %d\n",
		width, addrlen, hp);

	switch (width) {
	case SPI_NBITS_SINGLE:
		/* clear quad/dual mode */
		data &= ~(BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD |
			  BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL);
		break;
	case SPI_NBITS_QUAD:
		/* clear dual mode and set quad mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL;
		data |= BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD;
		break;
	case SPI_NBITS_DUAL:
		/* clear quad mode set dual mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_DATA_QUAD;
		data |= BSPI_STRAP_OVERRIDE_CTRL_DATA_DUAL;
		break;
	default:
		return -EINVAL;
	}

	if (addrlen == BSPI_ADDRLEN_4BYTES)
		/* set 4byte mode*/
		data |= BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE;
	else
		/* clear 4 byte mode */
		data &= ~BSPI_STRAP_OVERRIDE_CTRL_ADDR_4BYTE;

	/* set the override mode */
	data |=	BSPI_STRAP_OVERRIDE_CTRL_OVERRIDE;
	bcm_qspi_write(qspi, BSPI, BSPI_STRAP_OVERRIDE_CTRL, data);
	bcm_qspi_bspi_set_xfer_params(qspi, op->cmd.opcode, 0, 0, 0);

	return 0;
}