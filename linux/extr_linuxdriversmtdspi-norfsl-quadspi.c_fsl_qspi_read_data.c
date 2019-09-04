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
typedef  int /*<<< orphan*/  u32 ;
struct fsl_qspi {int /*<<< orphan*/  chip_base_addr; int /*<<< orphan*/  dev; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_RBDR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_qspi_endian_xchg (struct fsl_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qspi_readl (struct fsl_qspi*,scalar_t__) ; 

__attribute__((used)) static void fsl_qspi_read_data(struct fsl_qspi *q, int len, u8 *rxbuf)
{
	u32 tmp;
	int i = 0;

	while (len > 0) {
		tmp = qspi_readl(q, q->iobase + QUADSPI_RBDR + i * 4);
		tmp = fsl_qspi_endian_xchg(q, tmp);
		dev_dbg(q->dev, "chip addr:0x%.8x, rcv:0x%.8x\n",
				q->chip_base_addr, tmp);

		if (len >= 4) {
			*((u32 *)rxbuf) = tmp;
			rxbuf += 4;
		} else {
			memcpy(rxbuf, &tmp, len);
			break;
		}

		len -= 4;
		i++;
	}
}