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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {int /*<<< orphan*/  read_opcode; struct fsl_qspi* priv; } ;
struct fsl_qspi {scalar_t__ ahb_addr; scalar_t__ memmap_offs; scalar_t__ chip_base_addr; size_t memmap_len; scalar_t__ memmap_phy; int /*<<< orphan*/  dev; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 size_t ENOMEM ; 
 size_t QUADSPI_MIN_IOMAP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* ioremap_nocache (scalar_t__,size_t) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,size_t) ; 

__attribute__((used)) static ssize_t fsl_qspi_read(struct spi_nor *nor, loff_t from,
			     size_t len, u_char *buf)
{
	struct fsl_qspi *q = nor->priv;
	u8 cmd = nor->read_opcode;

	/* if necessary,ioremap buffer before AHB read, */
	if (!q->ahb_addr) {
		q->memmap_offs = q->chip_base_addr + from;
		q->memmap_len = len > QUADSPI_MIN_IOMAP ? len : QUADSPI_MIN_IOMAP;

		q->ahb_addr = ioremap_nocache(
				q->memmap_phy + q->memmap_offs,
				q->memmap_len);
		if (!q->ahb_addr) {
			dev_err(q->dev, "ioremap failed\n");
			return -ENOMEM;
		}
	/* ioremap if the data requested is out of range */
	} else if (q->chip_base_addr + from < q->memmap_offs
			|| q->chip_base_addr + from + len >
			q->memmap_offs + q->memmap_len) {
		iounmap(q->ahb_addr);

		q->memmap_offs = q->chip_base_addr + from;
		q->memmap_len = len > QUADSPI_MIN_IOMAP ? len : QUADSPI_MIN_IOMAP;
		q->ahb_addr = ioremap_nocache(
				q->memmap_phy + q->memmap_offs,
				q->memmap_len);
		if (!q->ahb_addr) {
			dev_err(q->dev, "ioremap failed\n");
			return -ENOMEM;
		}
	}

	dev_dbg(q->dev, "cmd [%x],read from %p, len:%zd\n",
		cmd, q->ahb_addr + q->chip_base_addr + from - q->memmap_offs,
		len);

	/* Read out the data directly from the AHB buffer.*/
	memcpy(buf, q->ahb_addr + q->chip_base_addr + from - q->memmap_offs,
		len);

	return len;
}