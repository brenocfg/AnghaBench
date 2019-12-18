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
typedef  int /*<<< orphan*/  u16 ;
struct if_spi_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_SPI_DEVICEID_CTRL_REG ; 
 int /*<<< orphan*/  IF_SPI_DEVICEID_CTRL_REG_TO_CARD_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IF_SPI_DEVICEID_CTRL_REG_TO_CARD_REV (int /*<<< orphan*/ ) ; 
 int spu_read_u32 (struct if_spi_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spu_get_chip_revision(struct if_spi_card *card,
				  u16 *card_id, u8 *card_rev)
{
	int err = 0;
	u32 dev_ctrl;
	err = spu_read_u32(card, IF_SPI_DEVICEID_CTRL_REG, &dev_ctrl);
	if (err)
		return err;
	*card_id = IF_SPI_DEVICEID_CTRL_REG_TO_CARD_ID(dev_ctrl);
	*card_rev = IF_SPI_DEVICEID_CTRL_REG_TO_CARD_REV(dev_ctrl);
	return err;
}