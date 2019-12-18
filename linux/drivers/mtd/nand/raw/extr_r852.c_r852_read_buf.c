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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct r852_device {scalar_t__ dma_usable; scalar_t__ card_unstable; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_DATALINE ; 
 int R852_DMA_LEN ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  r852_do_dma (struct r852_device*,int /*<<< orphan*/ *,int) ; 
 struct r852_device* r852_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_read_reg (struct r852_device*,int /*<<< orphan*/ ) ; 
 int r852_read_reg_dword (struct r852_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r852_read_buf(struct nand_chip *chip, uint8_t *buf, int len)
{
	struct r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	uint32_t reg;

	if (dev->card_unstable) {
		/* since we can't signal error here, at least, return
			predictable buffer */
		memset(buf, 0, len);
		return;
	}

	/* special case for whole sector read */
	if (len == R852_DMA_LEN && dev->dma_usable) {
		r852_do_dma(dev, buf, 1);
		return;
	}

	/* read in dword sized chunks */
	while (len >= 4) {

		reg = r852_read_reg_dword(dev, R852_DATALINE);
		*buf++ = reg & 0xFF;
		*buf++ = (reg >> 8) & 0xFF;
		*buf++ = (reg >> 16) & 0xFF;
		*buf++ = (reg >> 24) & 0xFF;
		len -= 4;
	}

	/* read the reset by bytes */
	while (len--)
		*buf++ = r852_read_reg(dev, R852_DATALINE);
}