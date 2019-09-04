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
struct TYPE_2__ {scalar_t__ partition_setting_completed; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_1__ ext_csd; } ;

/* Variables and functions */
 int EXT_CSD_GP_SIZE_MULT ; 
 size_t EXT_CSD_HC_ERASE_GRP_SIZE ; 
 size_t EXT_CSD_HC_WP_GRP_SIZE ; 
 size_t EXT_CSD_PARTITION_SUPPORT ; 
 scalar_t__ EXT_CSD_PART_CONFIG_ACC_GP0 ; 
 int EXT_CSD_PART_SUPPORT_PART_EN ; 
 int /*<<< orphan*/  MMC_BLK_DATA_AREA_GP ; 
 int MMC_NUM_GP_PARTITION ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_part_add (struct mmc_card*,unsigned int,scalar_t__,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmc_manage_gp_partitions(struct mmc_card *card, u8 *ext_csd)
{
	int idx;
	u8 hc_erase_grp_sz, hc_wp_grp_sz;
	unsigned int part_size;

	/*
	 * General purpose partition feature support --
	 * If ext_csd has the size of general purpose partitions,
	 * set size, part_cfg, partition name in mmc_part.
	 */
	if (ext_csd[EXT_CSD_PARTITION_SUPPORT] &
	    EXT_CSD_PART_SUPPORT_PART_EN) {
		hc_erase_grp_sz =
			ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
		hc_wp_grp_sz =
			ext_csd[EXT_CSD_HC_WP_GRP_SIZE];

		for (idx = 0; idx < MMC_NUM_GP_PARTITION; idx++) {
			if (!ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 1] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 2])
				continue;
			if (card->ext_csd.partition_setting_completed == 0) {
				pr_warn("%s: has partition size defined without partition complete\n",
					mmc_hostname(card->host));
				break;
			}
			part_size =
				(ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 2]
				<< 16) +
				(ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 1]
				<< 8) +
				ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3];
			part_size *= (size_t)(hc_erase_grp_sz *
				hc_wp_grp_sz);
			mmc_part_add(card, part_size << 19,
				EXT_CSD_PART_CONFIG_ACC_GP0 + idx,
				"gp%d", idx, false,
				MMC_BLK_DATA_AREA_GP);
		}
	}
}