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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct r852_device {scalar_t__ dma_usable; scalar_t__ card_unstable; } ;
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R852_DATALINE ; 
 int R852_DMA_LEN ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  r852_do_dma (struct r852_device*,int*,int /*<<< orphan*/ ) ; 
 struct r852_device* r852_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg (struct r852_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r852_write_reg_dword (struct r852_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void r852_write_buf(struct nand_chip *chip, const uint8_t *buf, int len)
{
	struct r852_device *dev = r852_get_dev(nand_to_mtd(chip));
	uint32_t reg;

	/* Don't allow any access to hardware if we suspect card removal */
	if (dev->card_unstable)
		return;

	/* Special case for whole sector read */
	if (len == R852_DMA_LEN && dev->dma_usable) {
		r852_do_dma(dev, (uint8_t *)buf, 0);
		return;
	}

	/* write DWORD chinks - faster */
	while (len >= 4) {
		reg = buf[0] | buf[1] << 8 | buf[2] << 16 | buf[3] << 24;
		r852_write_reg_dword(dev, R852_DATALINE, reg);
		buf += 4;
		len -= 4;

	}

	/* write rest */
	while (len > 0) {
		r852_write_reg(dev, R852_DATALINE, *buf++);
		len--;
	}
}