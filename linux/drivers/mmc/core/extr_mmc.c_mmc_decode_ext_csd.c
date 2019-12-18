#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int raw_ext_csd_structure; int rev; int* raw_sectors; int sectors; int strobe_support; int raw_card_type; int raw_s_a_timeout; int raw_erase_timeout_mult; int raw_hc_erase_grp_size; int part_config; int part_time; int sa_timeout; int erase_group_def; int hc_erase_timeout; int hc_erase_size; int rel_sectors; int raw_hc_erase_gap_size; int raw_sec_trim_mult; int raw_sec_erase_mult; int raw_sec_feature_support; int raw_trim_mult; int raw_partition_support; int raw_driver_strength; int partition_setting_completed; int sec_trim_mult; int sec_erase_mult; int sec_feature_support; int trim_timeout; int boot_ro_lock; int boot_ro_lockable; int raw_pwr_cl_52_195; int raw_pwr_cl_26_195; int raw_pwr_cl_52_360; int raw_pwr_cl_26_360; int raw_pwr_cl_200_195; int raw_pwr_cl_200_360; int raw_pwr_cl_ddr_52_195; int raw_pwr_cl_ddr_52_360; int raw_pwr_cl_ddr_200_360; int bkops; int man_bkops_en; int raw_bkops_status; int auto_bkops_en; int hpi; int out_of_int_time; int rel_param; int rst_n_function; int raw_rpmb_size_mult; int raw_erased_mem_count; int generic_cmd6_time; int power_off_longtime; int cache_size; int data_sector_size; unsigned int data_tag_unit_size; int max_packed_writes; int max_packed_reads; int ffu_capable; int pre_eol_info; int device_life_time_est_typ_a; int device_life_time_est_typ_b; int cmdq_support; int cmdq_depth; int /*<<< orphan*/  fwrev; int /*<<< orphan*/  feature_support; int /*<<< orphan*/  hpi_cmd; } ;
struct TYPE_5__ {int year; } ;
struct TYPE_4__ {int structure; } ;
struct mmc_card {int erased_byte; TYPE_3__ ext_csd; int /*<<< orphan*/  host; TYPE_2__ cid; TYPE_1__ csd; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int DEFAULT_CMD6_TIMEOUT_MS ; 
 int EINVAL ; 
 int EXT_CSD_AUTO_BKOPS_MASK ; 
 size_t EXT_CSD_BKOPS_EN ; 
 size_t EXT_CSD_BKOPS_STATUS ; 
 size_t EXT_CSD_BKOPS_SUPPORT ; 
 size_t EXT_CSD_BOOT_MULT ; 
 size_t EXT_CSD_BOOT_WP ; 
 int EXT_CSD_CACHE_SIZE ; 
 size_t EXT_CSD_CARD_TYPE ; 
 size_t EXT_CSD_CMDQ_DEPTH ; 
 int EXT_CSD_CMDQ_DEPTH_MASK ; 
 size_t EXT_CSD_CMDQ_SUPPORT ; 
 int EXT_CSD_CMDQ_SUPPORTED ; 
 size_t EXT_CSD_DATA_SECTOR_SIZE ; 
 size_t EXT_CSD_DATA_TAG_SUPPORT ; 
 size_t EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A ; 
 size_t EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B ; 
 size_t EXT_CSD_DRIVER_STRENGTH ; 
 size_t EXT_CSD_ERASED_MEM_CONT ; 
 size_t EXT_CSD_ERASE_GROUP_DEF ; 
 size_t EXT_CSD_ERASE_TIMEOUT_MULT ; 
 size_t EXT_CSD_FIRMWARE_VERSION ; 
 size_t EXT_CSD_FW_CONFIG ; 
 size_t EXT_CSD_GENERIC_CMD6_TIME ; 
 size_t EXT_CSD_HC_ERASE_GRP_SIZE ; 
 size_t EXT_CSD_HC_WP_GRP_SIZE ; 
 size_t EXT_CSD_HPI_FEATURES ; 
 int EXT_CSD_MANUAL_BKOPS_MASK ; 
 size_t EXT_CSD_MAX_PACKED_READS ; 
 size_t EXT_CSD_MAX_PACKED_WRITES ; 
 size_t EXT_CSD_OUT_OF_INTERRUPT_TIME ; 
 size_t EXT_CSD_PARTITION_SETTING_COMPLETED ; 
 size_t EXT_CSD_PARTITION_SUPPORT ; 
 size_t EXT_CSD_PART_CONFIG ; 
 scalar_t__ EXT_CSD_PART_CONFIG_ACC_BOOT0 ; 
 scalar_t__ EXT_CSD_PART_CONFIG_ACC_RPMB ; 
 int EXT_CSD_PART_SETTING_COMPLETED ; 
 size_t EXT_CSD_PART_SWITCH_TIME ; 
 size_t EXT_CSD_POWER_OFF_LONG_TIME ; 
 size_t EXT_CSD_PRE_EOL_INFO ; 
 size_t EXT_CSD_PWR_CL_200_195 ; 
 size_t EXT_CSD_PWR_CL_200_360 ; 
 size_t EXT_CSD_PWR_CL_26_195 ; 
 size_t EXT_CSD_PWR_CL_26_360 ; 
 size_t EXT_CSD_PWR_CL_52_195 ; 
 size_t EXT_CSD_PWR_CL_52_360 ; 
 size_t EXT_CSD_PWR_CL_DDR_200_360 ; 
 size_t EXT_CSD_PWR_CL_DDR_52_195 ; 
 size_t EXT_CSD_PWR_CL_DDR_52_360 ; 
 size_t EXT_CSD_REL_WR_SEC_C ; 
 size_t EXT_CSD_REV ; 
 size_t EXT_CSD_RPMB_MULT ; 
 size_t EXT_CSD_RST_N_FUNCTION ; 
 int EXT_CSD_SEC_CNT ; 
 size_t EXT_CSD_SEC_ERASE_MULT ; 
 size_t EXT_CSD_SEC_FEATURE_SUPPORT ; 
 size_t EXT_CSD_SEC_TRIM_MULT ; 
 size_t EXT_CSD_STROBE_SUPPORT ; 
 size_t EXT_CSD_STRUCTURE ; 
 size_t EXT_CSD_SUPPORTED_MODE ; 
 size_t EXT_CSD_S_A_TIMEOUT ; 
 size_t EXT_CSD_TAG_UNIT_SIZE ; 
 size_t EXT_CSD_TRIM_MULT ; 
 size_t EXT_CSD_WR_REL_PARAM ; 
 int /*<<< orphan*/  MMC_BLK_DATA_AREA_BOOT ; 
 int /*<<< orphan*/  MMC_BLK_DATA_AREA_RPMB ; 
 int /*<<< orphan*/  MMC_DISCARD_FEATURE ; 
 int /*<<< orphan*/  MMC_FIRMWARE_LEN ; 
 int MMC_MIN_PART_SWITCH_TIME ; 
 int MMC_NUM_BOOT_PARTITION ; 
 int /*<<< orphan*/  MMC_SEND_STATUS ; 
 int /*<<< orphan*/  MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_boot_partition_access (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_card_broken_hpi (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_card_set_blockaddr (struct mmc_card*) ; 
 int /*<<< orphan*/  mmc_ext_csd_fixups ; 
 int /*<<< orphan*/  mmc_fixup_device (struct mmc_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_host_cmd23 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_manage_enhanced_area (struct mmc_card*,int*) ; 
 int /*<<< orphan*/  mmc_manage_gp_partitions (struct mmc_card*,int*) ; 
 struct device_node* mmc_of_find_child_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_part_add (struct mmc_card*,int,scalar_t__,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_select_card_type (struct mmc_card*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mmc_decode_ext_csd(struct mmc_card *card, u8 *ext_csd)
{
	int err = 0, idx;
	unsigned int part_size;
	struct device_node *np;
	bool broken_hpi = false;

	/* Version is coded in the CSD_STRUCTURE byte in the EXT_CSD register */
	card->ext_csd.raw_ext_csd_structure = ext_csd[EXT_CSD_STRUCTURE];
	if (card->csd.structure == 3) {
		if (card->ext_csd.raw_ext_csd_structure > 2) {
			pr_err("%s: unrecognised EXT_CSD structure "
				"version %d\n", mmc_hostname(card->host),
					card->ext_csd.raw_ext_csd_structure);
			err = -EINVAL;
			goto out;
		}
	}

	np = mmc_of_find_child_device(card->host, 0);
	if (np && of_device_is_compatible(np, "mmc-card"))
		broken_hpi = of_property_read_bool(np, "broken-hpi");
	of_node_put(np);

	/*
	 * The EXT_CSD format is meant to be forward compatible. As long
	 * as CSD_STRUCTURE does not change, all values for EXT_CSD_REV
	 * are authorized, see JEDEC JESD84-B50 section B.8.
	 */
	card->ext_csd.rev = ext_csd[EXT_CSD_REV];

	/* fixup device after ext_csd revision field is updated */
	mmc_fixup_device(card, mmc_ext_csd_fixups);

	card->ext_csd.raw_sectors[0] = ext_csd[EXT_CSD_SEC_CNT + 0];
	card->ext_csd.raw_sectors[1] = ext_csd[EXT_CSD_SEC_CNT + 1];
	card->ext_csd.raw_sectors[2] = ext_csd[EXT_CSD_SEC_CNT + 2];
	card->ext_csd.raw_sectors[3] = ext_csd[EXT_CSD_SEC_CNT + 3];
	if (card->ext_csd.rev >= 2) {
		card->ext_csd.sectors =
			ext_csd[EXT_CSD_SEC_CNT + 0] << 0 |
			ext_csd[EXT_CSD_SEC_CNT + 1] << 8 |
			ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
			ext_csd[EXT_CSD_SEC_CNT + 3] << 24;

		/* Cards with density > 2GiB are sector addressed */
		if (card->ext_csd.sectors > (2u * 1024 * 1024 * 1024) / 512)
			mmc_card_set_blockaddr(card);
	}

	card->ext_csd.strobe_support = ext_csd[EXT_CSD_STROBE_SUPPORT];
	card->ext_csd.raw_card_type = ext_csd[EXT_CSD_CARD_TYPE];
	mmc_select_card_type(card);

	card->ext_csd.raw_s_a_timeout = ext_csd[EXT_CSD_S_A_TIMEOUT];
	card->ext_csd.raw_erase_timeout_mult =
		ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
	card->ext_csd.raw_hc_erase_grp_size =
		ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
	if (card->ext_csd.rev >= 3) {
		u8 sa_shift = ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.part_config = ext_csd[EXT_CSD_PART_CONFIG];

		/* EXT_CSD value is in units of 10ms, but we store in ms */
		card->ext_csd.part_time = 10 * ext_csd[EXT_CSD_PART_SWITCH_TIME];
		/* Some eMMC set the value too low so set a minimum */
		if (card->ext_csd.part_time &&
		    card->ext_csd.part_time < MMC_MIN_PART_SWITCH_TIME)
			card->ext_csd.part_time = MMC_MIN_PART_SWITCH_TIME;

		/* Sleep / awake timeout in 100ns units */
		if (sa_shift > 0 && sa_shift <= 0x17)
			card->ext_csd.sa_timeout =
					1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.erase_group_def =
			ext_csd[EXT_CSD_ERASE_GROUP_DEF];
		card->ext_csd.hc_erase_timeout = 300 *
			ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
		card->ext_csd.hc_erase_size =
			ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE] << 10;

		card->ext_csd.rel_sectors = ext_csd[EXT_CSD_REL_WR_SEC_C];

		/*
		 * There are two boot regions of equal size, defined in
		 * multiples of 128K.
		 */
		if (ext_csd[EXT_CSD_BOOT_MULT] && mmc_boot_partition_access(card->host)) {
			for (idx = 0; idx < MMC_NUM_BOOT_PARTITION; idx++) {
				part_size = ext_csd[EXT_CSD_BOOT_MULT] << 17;
				mmc_part_add(card, part_size,
					EXT_CSD_PART_CONFIG_ACC_BOOT0 + idx,
					"boot%d", idx, true,
					MMC_BLK_DATA_AREA_BOOT);
			}
		}
	}

	card->ext_csd.raw_hc_erase_gap_size =
		ext_csd[EXT_CSD_HC_WP_GRP_SIZE];
	card->ext_csd.raw_sec_trim_mult =
		ext_csd[EXT_CSD_SEC_TRIM_MULT];
	card->ext_csd.raw_sec_erase_mult =
		ext_csd[EXT_CSD_SEC_ERASE_MULT];
	card->ext_csd.raw_sec_feature_support =
		ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
	card->ext_csd.raw_trim_mult =
		ext_csd[EXT_CSD_TRIM_MULT];
	card->ext_csd.raw_partition_support = ext_csd[EXT_CSD_PARTITION_SUPPORT];
	card->ext_csd.raw_driver_strength = ext_csd[EXT_CSD_DRIVER_STRENGTH];
	if (card->ext_csd.rev >= 4) {
		if (ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED] &
		    EXT_CSD_PART_SETTING_COMPLETED)
			card->ext_csd.partition_setting_completed = 1;
		else
			card->ext_csd.partition_setting_completed = 0;

		mmc_manage_enhanced_area(card, ext_csd);

		mmc_manage_gp_partitions(card, ext_csd);

		card->ext_csd.sec_trim_mult =
			ext_csd[EXT_CSD_SEC_TRIM_MULT];
		card->ext_csd.sec_erase_mult =
			ext_csd[EXT_CSD_SEC_ERASE_MULT];
		card->ext_csd.sec_feature_support =
			ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
		card->ext_csd.trim_timeout = 300 *
			ext_csd[EXT_CSD_TRIM_MULT];

		/*
		 * Note that the call to mmc_part_add above defaults to read
		 * only. If this default assumption is changed, the call must
		 * take into account the value of boot_locked below.
		 */
		card->ext_csd.boot_ro_lock = ext_csd[EXT_CSD_BOOT_WP];
		card->ext_csd.boot_ro_lockable = true;

		/* Save power class values */
		card->ext_csd.raw_pwr_cl_52_195 =
			ext_csd[EXT_CSD_PWR_CL_52_195];
		card->ext_csd.raw_pwr_cl_26_195 =
			ext_csd[EXT_CSD_PWR_CL_26_195];
		card->ext_csd.raw_pwr_cl_52_360 =
			ext_csd[EXT_CSD_PWR_CL_52_360];
		card->ext_csd.raw_pwr_cl_26_360 =
			ext_csd[EXT_CSD_PWR_CL_26_360];
		card->ext_csd.raw_pwr_cl_200_195 =
			ext_csd[EXT_CSD_PWR_CL_200_195];
		card->ext_csd.raw_pwr_cl_200_360 =
			ext_csd[EXT_CSD_PWR_CL_200_360];
		card->ext_csd.raw_pwr_cl_ddr_52_195 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_195];
		card->ext_csd.raw_pwr_cl_ddr_52_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_360];
		card->ext_csd.raw_pwr_cl_ddr_200_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_200_360];
	}

	if (card->ext_csd.rev >= 5) {
		/* Adjust production date as per JEDEC JESD84-B451 */
		if (card->cid.year < 2010)
			card->cid.year += 16;

		/* check whether the eMMC card supports BKOPS */
		if (ext_csd[EXT_CSD_BKOPS_SUPPORT] & 0x1) {
			card->ext_csd.bkops = 1;
			card->ext_csd.man_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_MANUAL_BKOPS_MASK);
			card->ext_csd.raw_bkops_status =
				ext_csd[EXT_CSD_BKOPS_STATUS];
			if (card->ext_csd.man_bkops_en)
				pr_debug("%s: MAN_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
			card->ext_csd.auto_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_AUTO_BKOPS_MASK);
			if (card->ext_csd.auto_bkops_en)
				pr_debug("%s: AUTO_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
		}

		/* check whether the eMMC card supports HPI */
		if (!mmc_card_broken_hpi(card) &&
		    !broken_hpi && (ext_csd[EXT_CSD_HPI_FEATURES] & 0x1)) {
			card->ext_csd.hpi = 1;
			if (ext_csd[EXT_CSD_HPI_FEATURES] & 0x2)
				card->ext_csd.hpi_cmd =	MMC_STOP_TRANSMISSION;
			else
				card->ext_csd.hpi_cmd = MMC_SEND_STATUS;
			/*
			 * Indicate the maximum timeout to close
			 * a command interrupted by HPI
			 */
			card->ext_csd.out_of_int_time =
				ext_csd[EXT_CSD_OUT_OF_INTERRUPT_TIME] * 10;
		}

		card->ext_csd.rel_param = ext_csd[EXT_CSD_WR_REL_PARAM];
		card->ext_csd.rst_n_function = ext_csd[EXT_CSD_RST_N_FUNCTION];

		/*
		 * RPMB regions are defined in multiples of 128K.
		 */
		card->ext_csd.raw_rpmb_size_mult = ext_csd[EXT_CSD_RPMB_MULT];
		if (ext_csd[EXT_CSD_RPMB_MULT] && mmc_host_cmd23(card->host)) {
			mmc_part_add(card, ext_csd[EXT_CSD_RPMB_MULT] << 17,
				EXT_CSD_PART_CONFIG_ACC_RPMB,
				"rpmb", 0, false,
				MMC_BLK_DATA_AREA_RPMB);
		}
	}

	card->ext_csd.raw_erased_mem_count = ext_csd[EXT_CSD_ERASED_MEM_CONT];
	if (ext_csd[EXT_CSD_ERASED_MEM_CONT])
		card->erased_byte = 0xFF;
	else
		card->erased_byte = 0x0;

	/* eMMC v4.5 or later */
	card->ext_csd.generic_cmd6_time = DEFAULT_CMD6_TIMEOUT_MS;
	if (card->ext_csd.rev >= 6) {
		card->ext_csd.feature_support |= MMC_DISCARD_FEATURE;

		card->ext_csd.generic_cmd6_time = 10 *
			ext_csd[EXT_CSD_GENERIC_CMD6_TIME];
		card->ext_csd.power_off_longtime = 10 *
			ext_csd[EXT_CSD_POWER_OFF_LONG_TIME];

		card->ext_csd.cache_size =
			ext_csd[EXT_CSD_CACHE_SIZE + 0] << 0 |
			ext_csd[EXT_CSD_CACHE_SIZE + 1] << 8 |
			ext_csd[EXT_CSD_CACHE_SIZE + 2] << 16 |
			ext_csd[EXT_CSD_CACHE_SIZE + 3] << 24;

		if (ext_csd[EXT_CSD_DATA_SECTOR_SIZE] == 1)
			card->ext_csd.data_sector_size = 4096;
		else
			card->ext_csd.data_sector_size = 512;

		if ((ext_csd[EXT_CSD_DATA_TAG_SUPPORT] & 1) &&
		    (ext_csd[EXT_CSD_TAG_UNIT_SIZE] <= 8)) {
			card->ext_csd.data_tag_unit_size =
			((unsigned int) 1 << ext_csd[EXT_CSD_TAG_UNIT_SIZE]) *
			(card->ext_csd.data_sector_size);
		} else {
			card->ext_csd.data_tag_unit_size = 0;
		}

		card->ext_csd.max_packed_writes =
			ext_csd[EXT_CSD_MAX_PACKED_WRITES];
		card->ext_csd.max_packed_reads =
			ext_csd[EXT_CSD_MAX_PACKED_READS];
	} else {
		card->ext_csd.data_sector_size = 512;
	}

	/* eMMC v5 or later */
	if (card->ext_csd.rev >= 7) {
		memcpy(card->ext_csd.fwrev, &ext_csd[EXT_CSD_FIRMWARE_VERSION],
		       MMC_FIRMWARE_LEN);
		card->ext_csd.ffu_capable =
			(ext_csd[EXT_CSD_SUPPORTED_MODE] & 0x1) &&
			!(ext_csd[EXT_CSD_FW_CONFIG] & 0x1);

		card->ext_csd.pre_eol_info = ext_csd[EXT_CSD_PRE_EOL_INFO];
		card->ext_csd.device_life_time_est_typ_a =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A];
		card->ext_csd.device_life_time_est_typ_b =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B];
	}

	/* eMMC v5.1 or later */
	if (card->ext_csd.rev >= 8) {
		card->ext_csd.cmdq_support = ext_csd[EXT_CSD_CMDQ_SUPPORT] &
					     EXT_CSD_CMDQ_SUPPORTED;
		card->ext_csd.cmdq_depth = (ext_csd[EXT_CSD_CMDQ_DEPTH] &
					    EXT_CSD_CMDQ_DEPTH_MASK) + 1;
		/* Exclude inefficiently small queue depths */
		if (card->ext_csd.cmdq_depth <= 2) {
			card->ext_csd.cmdq_support = false;
			card->ext_csd.cmdq_depth = 0;
		}
		if (card->ext_csd.cmdq_support) {
			pr_debug("%s: Command Queue supported depth %u\n",
				 mmc_hostname(card->host),
				 card->ext_csd.cmdq_depth);
		}
	}
out:
	return err;
}