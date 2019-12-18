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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct ms_delay_write_tag {int delay_write_flag; scalar_t__ logblock; scalar_t__ pageoff; scalar_t__ old_phyblock; scalar_t__ new_phyblock; } ;
struct ms_info {int block_shift; int page_off; TYPE_1__* segment; scalar_t__ cleanup_counter; struct ms_delay_write_tag delay_write; } ;
struct rtsx_chip {int /*<<< orphan*/  card_fail; struct ms_info ms_card; } ;
struct TYPE_2__ {scalar_t__ build_flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  MS_CARD ; 
 int /*<<< orphan*/  MS_NO_ERROR ; 
 unsigned int SCSI_LUN (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_NOT_PRESENT ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR ; 
 int /*<<< orphan*/  SENSE_TYPE_MEDIA_WRITE_ERR ; 
 int STATUS_FAIL ; 
 int STATUS_SUCCESS ; 
 int detect_card_cd (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int ms_build_l2p_tbl (struct rtsx_chip*,int) ; 
 int ms_copy_page (struct rtsx_chip*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int ms_delay_write (struct rtsx_chip*) ; 
 int ms_erase_block (struct rtsx_chip*,scalar_t__) ; 
 int ms_finish_write (struct rtsx_chip*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ms_get_l2p_tbl (struct rtsx_chip*,int,scalar_t__) ; 
 scalar_t__ ms_get_unused_block (struct rtsx_chip*,int) ; 
 int ms_prepare_write (struct rtsx_chip*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int ms_read_multiple_pages (struct rtsx_chip*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ms_rw_fail (struct scsi_cmnd*,struct rtsx_chip*) ; 
 int /*<<< orphan*/  ms_set_err_code (struct rtsx_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ms_set_l2p_tbl (struct rtsx_chip*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ms_set_unused_block (struct rtsx_chip*,scalar_t__) ; 
 scalar_t__* ms_start_idx ; 
 int ms_switch_clock (struct rtsx_chip*) ; 
 int ms_write_multiple_pages (struct rtsx_chip*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  rtsx_dev (struct rtsx_chip*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  set_sense_type (struct rtsx_chip*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  toggle_gpio (struct rtsx_chip*,int) ; 

__attribute__((used)) static int ms_rw_multi_sector(struct scsi_cmnd *srb, struct rtsx_chip *chip,
			      u32 start_sector, u16 sector_cnt)
{
	struct ms_info *ms_card = &chip->ms_card;
	unsigned int lun = SCSI_LUN(srb);
	int retval, seg_no;
	unsigned int index = 0, offset = 0;
	u16 old_blk = 0, new_blk = 0, log_blk, total_sec_cnt = sector_cnt;
	u8 start_page, end_page = 0, page_cnt;
	u8 *ptr;
#ifdef MS_DELAY_WRITE
	struct ms_delay_write_tag *delay_write = &ms_card->delay_write;
#endif

	ms_set_err_code(chip, MS_NO_ERROR);

	ms_card->cleanup_counter = 0;

	ptr = (u8 *)scsi_sglist(srb);

	retval = ms_switch_clock(chip);
	if (retval != STATUS_SUCCESS) {
		ms_rw_fail(srb, chip);
		return STATUS_FAIL;
	}

	log_blk = (u16)(start_sector >> ms_card->block_shift);
	start_page = (u8)(start_sector & ms_card->page_off);

	for (seg_no = 0; seg_no < ARRAY_SIZE(ms_start_idx) - 1; seg_no++) {
		if (log_blk < ms_start_idx[seg_no + 1])
			break;
	}

	if (ms_card->segment[seg_no].build_flag == 0) {
		retval = ms_build_l2p_tbl(chip, seg_no);
		if (retval != STATUS_SUCCESS) {
			chip->card_fail |= MS_CARD;
			set_sense_type(chip, lun, SENSE_TYPE_MEDIA_NOT_PRESENT);
			return STATUS_FAIL;
		}
	}

	if (srb->sc_data_direction == DMA_TO_DEVICE) {
#ifdef MS_DELAY_WRITE
		if (delay_write->delay_write_flag &&
		    (delay_write->logblock == log_blk) &&
		    (start_page > delay_write->pageoff)) {
			delay_write->delay_write_flag = 0;
			retval = ms_copy_page(chip,
					      delay_write->old_phyblock,
					      delay_write->new_phyblock,
					      log_blk,
					      delay_write->pageoff, start_page);
			if (retval != STATUS_SUCCESS) {
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				return STATUS_FAIL;
			}
			old_blk = delay_write->old_phyblock;
			new_blk = delay_write->new_phyblock;
		} else if (delay_write->delay_write_flag &&
				(delay_write->logblock == log_blk) &&
				(start_page == delay_write->pageoff)) {
			delay_write->delay_write_flag = 0;
			old_blk = delay_write->old_phyblock;
			new_blk = delay_write->new_phyblock;
		} else {
			retval = ms_delay_write(chip);
			if (retval != STATUS_SUCCESS) {
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				return STATUS_FAIL;
			}
#endif
			old_blk = ms_get_l2p_tbl
					(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
			new_blk  = ms_get_unused_block(chip, seg_no);
			if ((old_blk == 0xFFFF) || (new_blk == 0xFFFF)) {
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				return STATUS_FAIL;
			}

			retval = ms_prepare_write(chip, old_blk, new_blk,
						  log_blk, start_page);
			if (retval != STATUS_SUCCESS) {
				if (detect_card_cd(chip, MS_CARD) !=
				    STATUS_SUCCESS) {
					set_sense_type
						(chip, lun,
						SENSE_TYPE_MEDIA_NOT_PRESENT);
					return STATUS_FAIL;
				}
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_WRITE_ERR);
				return STATUS_FAIL;
			}
#ifdef MS_DELAY_WRITE
		}
#endif
	} else {
#ifdef MS_DELAY_WRITE
		retval = ms_delay_write(chip);
		if (retval != STATUS_SUCCESS) {
			if (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) {
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				return STATUS_FAIL;
			}
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			return STATUS_FAIL;
		}
#endif
		old_blk = ms_get_l2p_tbl(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
		if (old_blk == 0xFFFF) {
			set_sense_type(chip, lun,
				       SENSE_TYPE_MEDIA_UNRECOVER_READ_ERR);
			return STATUS_FAIL;
		}
	}

	dev_dbg(rtsx_dev(chip), "seg_no = %d, old_blk = 0x%x, new_blk = 0x%x\n",
		seg_no, old_blk, new_blk);

	while (total_sec_cnt) {
		if ((start_page + total_sec_cnt) > (ms_card->page_off + 1))
			end_page = ms_card->page_off + 1;
		else
			end_page = start_page + (u8)total_sec_cnt;

		page_cnt = end_page - start_page;

		dev_dbg(rtsx_dev(chip), "start_page = %d, end_page = %d, page_cnt = %d\n",
			start_page, end_page, page_cnt);

		if (srb->sc_data_direction == DMA_FROM_DEVICE) {
			retval = ms_read_multiple_pages(chip,
							old_blk, log_blk,
							start_page, end_page,
							ptr, &index, &offset);
		} else {
			retval = ms_write_multiple_pages(chip, old_blk, new_blk,
							 log_blk, start_page,
							 end_page, ptr, &index,
							 &offset);
		}

		if (retval != STATUS_SUCCESS) {
			toggle_gpio(chip, 1);
			if (detect_card_cd(chip, MS_CARD) != STATUS_SUCCESS) {
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				return STATUS_FAIL;
			}
			ms_rw_fail(srb, chip);
			return STATUS_FAIL;
		}

		if (srb->sc_data_direction == DMA_TO_DEVICE) {
			if (end_page == (ms_card->page_off + 1)) {
				retval = ms_erase_block(chip, old_blk);
				if (retval == STATUS_SUCCESS)
					ms_set_unused_block(chip, old_blk);

				ms_set_l2p_tbl(chip, seg_no,
					       log_blk - ms_start_idx[seg_no],
					       new_blk);
			}
		}

		total_sec_cnt -= page_cnt;
		if (scsi_sg_count(srb) == 0)
			ptr += page_cnt * 512;

		if (total_sec_cnt == 0)
			break;

		log_blk++;

		for (seg_no = 0; seg_no < ARRAY_SIZE(ms_start_idx) - 1;
				seg_no++) {
			if (log_blk < ms_start_idx[seg_no + 1])
				break;
		}

		if (ms_card->segment[seg_no].build_flag == 0) {
			retval = ms_build_l2p_tbl(chip, seg_no);
			if (retval != STATUS_SUCCESS) {
				chip->card_fail |= MS_CARD;
				set_sense_type(chip, lun,
					       SENSE_TYPE_MEDIA_NOT_PRESENT);
				return STATUS_FAIL;
			}
		}

		old_blk = ms_get_l2p_tbl(chip, seg_no,
					 log_blk - ms_start_idx[seg_no]);
		if (old_blk == 0xFFFF) {
			ms_rw_fail(srb, chip);
			return STATUS_FAIL;
		}

		if (srb->sc_data_direction == DMA_TO_DEVICE) {
			new_blk = ms_get_unused_block(chip, seg_no);
			if (new_blk == 0xFFFF) {
				ms_rw_fail(srb, chip);
				return STATUS_FAIL;
			}
		}

		dev_dbg(rtsx_dev(chip), "seg_no = %d, old_blk = 0x%x, new_blk = 0x%x\n",
			seg_no, old_blk, new_blk);

		start_page = 0;
	}

	if (srb->sc_data_direction == DMA_TO_DEVICE) {
		if (end_page < (ms_card->page_off + 1)) {
#ifdef MS_DELAY_WRITE
			delay_write->delay_write_flag = 1;
			delay_write->old_phyblock = old_blk;
			delay_write->new_phyblock = new_blk;
			delay_write->logblock = log_blk;
			delay_write->pageoff = end_page;
#else
			retval = ms_finish_write(chip, old_blk, new_blk,
						 log_blk, end_page);
			if (retval != STATUS_SUCCESS) {
				if (detect_card_cd(chip, MS_CARD) !=
				    STATUS_SUCCESS) {
					set_sense_type
						(chip, lun,
						SENSE_TYPE_MEDIA_NOT_PRESENT);
					return STATUS_FAIL;
				}

				ms_rw_fail(srb, chip);
				return STATUS_FAIL;
			}
#endif
		}
	}

	scsi_set_resid(srb, 0);

	return STATUS_SUCCESS;
}