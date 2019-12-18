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
struct TYPE_2__ {scalar_t__ raw_partition_support; scalar_t__ raw_erased_mem_count; scalar_t__ rev; scalar_t__ raw_ext_csd_structure; scalar_t__ raw_card_type; scalar_t__ raw_s_a_timeout; scalar_t__ raw_hc_erase_gap_size; scalar_t__ raw_erase_timeout_mult; scalar_t__ raw_hc_erase_grp_size; scalar_t__ raw_sec_trim_mult; scalar_t__ raw_sec_erase_mult; scalar_t__ raw_sec_feature_support; scalar_t__ raw_trim_mult; scalar_t__* raw_sectors; scalar_t__ raw_pwr_cl_52_195; scalar_t__ raw_pwr_cl_26_195; scalar_t__ raw_pwr_cl_52_360; scalar_t__ raw_pwr_cl_26_360; scalar_t__ raw_pwr_cl_200_195; scalar_t__ raw_pwr_cl_200_360; scalar_t__ raw_pwr_cl_ddr_52_195; scalar_t__ raw_pwr_cl_ddr_52_360; scalar_t__ raw_pwr_cl_ddr_200_360; } ;
struct mmc_card {TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EXT_CSD_CARD_TYPE ; 
 size_t EXT_CSD_ERASED_MEM_CONT ; 
 size_t EXT_CSD_ERASE_TIMEOUT_MULT ; 
 size_t EXT_CSD_HC_ERASE_GRP_SIZE ; 
 size_t EXT_CSD_HC_WP_GRP_SIZE ; 
 size_t EXT_CSD_PARTITION_SUPPORT ; 
 size_t EXT_CSD_PWR_CL_200_195 ; 
 size_t EXT_CSD_PWR_CL_200_360 ; 
 size_t EXT_CSD_PWR_CL_26_195 ; 
 size_t EXT_CSD_PWR_CL_26_360 ; 
 size_t EXT_CSD_PWR_CL_52_195 ; 
 size_t EXT_CSD_PWR_CL_52_360 ; 
 size_t EXT_CSD_PWR_CL_DDR_200_360 ; 
 size_t EXT_CSD_PWR_CL_DDR_52_195 ; 
 size_t EXT_CSD_PWR_CL_DDR_52_360 ; 
 size_t EXT_CSD_REV ; 
 int EXT_CSD_SEC_CNT ; 
 size_t EXT_CSD_SEC_ERASE_MULT ; 
 size_t EXT_CSD_SEC_FEATURE_SUPPORT ; 
 size_t EXT_CSD_SEC_TRIM_MULT ; 
 size_t EXT_CSD_STRUCTURE ; 
 size_t EXT_CSD_S_A_TIMEOUT ; 
 size_t EXT_CSD_TRIM_MULT ; 
 unsigned int MMC_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 int mmc_get_ext_csd (struct mmc_card*,scalar_t__**) ; 

__attribute__((used)) static int mmc_compare_ext_csds(struct mmc_card *card, unsigned bus_width)
{
	u8 *bw_ext_csd;
	int err;

	if (bus_width == MMC_BUS_WIDTH_1)
		return 0;

	err = mmc_get_ext_csd(card, &bw_ext_csd);
	if (err)
		return err;

	/* only compare read only fields */
	err = !((card->ext_csd.raw_partition_support ==
			bw_ext_csd[EXT_CSD_PARTITION_SUPPORT]) &&
		(card->ext_csd.raw_erased_mem_count ==
			bw_ext_csd[EXT_CSD_ERASED_MEM_CONT]) &&
		(card->ext_csd.rev ==
			bw_ext_csd[EXT_CSD_REV]) &&
		(card->ext_csd.raw_ext_csd_structure ==
			bw_ext_csd[EXT_CSD_STRUCTURE]) &&
		(card->ext_csd.raw_card_type ==
			bw_ext_csd[EXT_CSD_CARD_TYPE]) &&
		(card->ext_csd.raw_s_a_timeout ==
			bw_ext_csd[EXT_CSD_S_A_TIMEOUT]) &&
		(card->ext_csd.raw_hc_erase_gap_size ==
			bw_ext_csd[EXT_CSD_HC_WP_GRP_SIZE]) &&
		(card->ext_csd.raw_erase_timeout_mult ==
			bw_ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT]) &&
		(card->ext_csd.raw_hc_erase_grp_size ==
			bw_ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]) &&
		(card->ext_csd.raw_sec_trim_mult ==
			bw_ext_csd[EXT_CSD_SEC_TRIM_MULT]) &&
		(card->ext_csd.raw_sec_erase_mult ==
			bw_ext_csd[EXT_CSD_SEC_ERASE_MULT]) &&
		(card->ext_csd.raw_sec_feature_support ==
			bw_ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT]) &&
		(card->ext_csd.raw_trim_mult ==
			bw_ext_csd[EXT_CSD_TRIM_MULT]) &&
		(card->ext_csd.raw_sectors[0] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 0]) &&
		(card->ext_csd.raw_sectors[1] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 1]) &&
		(card->ext_csd.raw_sectors[2] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 2]) &&
		(card->ext_csd.raw_sectors[3] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 3]) &&
		(card->ext_csd.raw_pwr_cl_52_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_52_195]) &&
		(card->ext_csd.raw_pwr_cl_26_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_26_195]) &&
		(card->ext_csd.raw_pwr_cl_52_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_52_360]) &&
		(card->ext_csd.raw_pwr_cl_26_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_26_360]) &&
		(card->ext_csd.raw_pwr_cl_200_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_200_195]) &&
		(card->ext_csd.raw_pwr_cl_200_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_200_360]) &&
		(card->ext_csd.raw_pwr_cl_ddr_52_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_195]) &&
		(card->ext_csd.raw_pwr_cl_ddr_52_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_360]) &&
		(card->ext_csd.raw_pwr_cl_ddr_200_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_200_360]));

	if (err)
		err = -EINVAL;

	kfree(bw_ext_csd);
	return err;
}