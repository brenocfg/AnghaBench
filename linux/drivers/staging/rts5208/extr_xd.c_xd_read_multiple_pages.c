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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct xd_info {int block_shift; scalar_t__ page_off; } ;
struct rtsx_chip {int /*<<< orphan*/  xd_timeout; TYPE_1__* srb; struct xd_info xd_card; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_data_direction; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DATA_SOURCE ; 
 int /*<<< orphan*/  CHECK_REG_CMD ; 
 int /*<<< orphan*/  DMA_512 ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ETIMEDOUT ; 
 int NO_NEW_BLK ; 
 int RING_BUFFER ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int XD_AUTO_CHK_DATA_STATUS ; 
 int /*<<< orphan*/  XD_CARD ; 
 int /*<<< orphan*/  XD_CFG ; 
 int /*<<< orphan*/  XD_CHK_BAD_NEWBLK (struct xd_info*) ; 
 int /*<<< orphan*/  XD_CHK_DATA_STATUS ; 
 int /*<<< orphan*/  XD_CLR_BAD_NEWBLK (struct xd_info*) ; 
 int /*<<< orphan*/  XD_CLR_BAD_OLDBLK (struct xd_info*) ; 
 int /*<<< orphan*/  XD_CTL ; 
 int XD_ECC1_ERROR ; 
 int XD_ECC1_UNCORRECTABLE ; 
 int XD_ECC2_ERROR ; 
 int XD_ECC2_UNCORRECTABLE ; 
 int /*<<< orphan*/  XD_ECC_ERROR ; 
 int XD_GPG ; 
 int /*<<< orphan*/  XD_NO_CARD ; 
 int /*<<< orphan*/  XD_PAGE_CNT ; 
 int /*<<< orphan*/  XD_PAGE_STATUS ; 
 int XD_PPB_EMPTY ; 
 int XD_PPB_TO_SIE ; 
 int /*<<< orphan*/  XD_PRG_ERROR ; 
 int XD_READ_PAGES ; 
 int /*<<< orphan*/  XD_RW_ADDR ; 
 int /*<<< orphan*/  XD_TO_ERROR ; 
 int /*<<< orphan*/  XD_TRANSFER ; 
 int XD_TRANSFER_END ; 
 int XD_TRANSFER_START ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_add_cmd (struct rtsx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtsx_clear_xd_error (struct rtsx_chip*) ; 
 int /*<<< orphan*/  rtsx_init_cmd (struct rtsx_chip*) ; 
 int rtsx_read_register (struct rtsx_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtsx_send_cmd_no_wait (struct rtsx_chip*) ; 
 int rtsx_transfer_data_partial (struct rtsx_chip*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_sg_count (TYPE_1__*) ; 
 int /*<<< orphan*/  trans_dma_enable (int /*<<< orphan*/ ,struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timeout (int) ; 
 int /*<<< orphan*/  xd_assign_phy_addr (struct rtsx_chip*,int,int /*<<< orphan*/ ) ; 
 int xd_copy_page (struct rtsx_chip*,int,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int xd_erase_block (struct rtsx_chip*,int) ; 
 int xd_get_unused_block (struct rtsx_chip*,int) ; 
 int /*<<< orphan*/  xd_mark_bad_block (struct rtsx_chip*,int) ; 
 int xd_read_redundant (struct rtsx_chip*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xd_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xd_set_l2p_tbl (struct rtsx_chip*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xd_set_unused_block (struct rtsx_chip*,int) ; 

__attribute__((used)) static int xd_read_multiple_pages(struct rtsx_chip *chip, u32 phy_blk,
				  u32 log_blk, u8 start_page, u8 end_page,
				  u8 *buf, unsigned int *index,
				  unsigned int *offset)
{
	struct xd_info *xd_card = &chip->xd_card;
	u32 page_addr, new_blk;
	u16 log_off;
	u8 reg_val, page_cnt;
	int zone_no, retval, i;

	if (start_page > end_page)
		goto status_fail;

	page_cnt = end_page - start_page;
	zone_no = (int)(log_blk / 1000);
	log_off = (u16)(log_blk % 1000);

	if ((phy_blk & 0x3FF) == 0x3FF) {
		for (i = 0; i < 256; i++) {
			page_addr = ((u32)i) << xd_card->block_shift;

			retval = xd_read_redundant(chip, page_addr, NULL, 0);
			if (retval == STATUS_SUCCESS)
				break;

			if (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) {
				xd_set_err_code(chip, XD_NO_CARD);
				goto status_fail;
			}
		}
	}

	page_addr = (phy_blk << xd_card->block_shift) + start_page;

	rtsx_init_cmd(chip);

	xd_assign_phy_addr(chip, page_addr, XD_RW_ADDR);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CFG, XD_PPB_TO_SIE, XD_PPB_TO_SIE);
	rtsx_add_cmd(chip, WRITE_REG_CMD, CARD_DATA_SOURCE, 0x01, RING_BUFFER);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_PAGE_CNT, 0xFF, page_cnt);
	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_CHK_DATA_STATUS,
		     XD_AUTO_CHK_DATA_STATUS, XD_AUTO_CHK_DATA_STATUS);

	trans_dma_enable(chip->srb->sc_data_direction, chip,
			 page_cnt * 512, DMA_512);

	rtsx_add_cmd(chip, WRITE_REG_CMD, XD_TRANSFER, 0xFF,
		     XD_TRANSFER_START | XD_READ_PAGES);
	rtsx_add_cmd(chip, CHECK_REG_CMD, XD_TRANSFER,
		     XD_TRANSFER_END | XD_PPB_EMPTY,
		     XD_TRANSFER_END | XD_PPB_EMPTY);

	rtsx_send_cmd_no_wait(chip);

	retval = rtsx_transfer_data_partial(chip, XD_CARD, buf, page_cnt * 512,
					    scsi_sg_count(chip->srb),
					    index, offset, DMA_FROM_DEVICE,
					    chip->xd_timeout);
	if (retval < 0) {
		rtsx_clear_xd_error(chip);

		if (retval == -ETIMEDOUT) {
			xd_set_err_code(chip, XD_TO_ERROR);
			goto status_fail;
		} else {
			goto fail;
		}
	}

	return STATUS_SUCCESS;

fail:
	retval = rtsx_read_register(chip, XD_PAGE_STATUS, &reg_val);
	if (retval)
		return retval;

	if (reg_val !=  XD_GPG)
		xd_set_err_code(chip, XD_PRG_ERROR);

	retval = rtsx_read_register(chip, XD_CTL, &reg_val);
	if (retval)
		return retval;

	if (((reg_val & (XD_ECC1_ERROR | XD_ECC1_UNCORRECTABLE)) ==
				(XD_ECC1_ERROR | XD_ECC1_UNCORRECTABLE)) ||
		((reg_val & (XD_ECC2_ERROR | XD_ECC2_UNCORRECTABLE)) ==
			(XD_ECC2_ERROR | XD_ECC2_UNCORRECTABLE))) {
		wait_timeout(100);

		if (detect_card_cd(chip, XD_CARD) != STATUS_SUCCESS) {
			xd_set_err_code(chip, XD_NO_CARD);
			goto status_fail;
		}

		xd_set_err_code(chip, XD_ECC_ERROR);

		new_blk = xd_get_unused_block(chip, zone_no);
		if (new_blk == NO_NEW_BLK) {
			XD_CLR_BAD_OLDBLK(xd_card);
			goto status_fail;
		}

		retval = xd_copy_page(chip, phy_blk, new_blk, 0,
				      xd_card->page_off + 1);
		if (retval != STATUS_SUCCESS) {
			if (!XD_CHK_BAD_NEWBLK(xd_card)) {
				retval = xd_erase_block(chip, new_blk);
				if (retval == STATUS_SUCCESS)
					xd_set_unused_block(chip, new_blk);
			} else {
				XD_CLR_BAD_NEWBLK(xd_card);
			}
			XD_CLR_BAD_OLDBLK(xd_card);
			goto status_fail;
		}
		xd_set_l2p_tbl(chip, zone_no, log_off, (u16)(new_blk & 0x3FF));
		xd_erase_block(chip, phy_blk);
		xd_mark_bad_block(chip, phy_blk);
		XD_CLR_BAD_OLDBLK(xd_card);
	}

status_fail:
	return STATUS_FAIL;
}