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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct stepping_info {char stepping; char substepping; } ;
struct intel_fw_info {scalar_t__ dmc_id; char substepping; char stepping; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_DEFAULT_FW_OFFSET ; 

__attribute__((used)) static u32 find_dmc_fw_offset(const struct intel_fw_info *fw_info,
			      unsigned int num_entries,
			      const struct stepping_info *si,
			      u8 package_ver)
{
	u32 dmc_offset = CSR_DEFAULT_FW_OFFSET;
	unsigned int i;

	for (i = 0; i < num_entries; i++) {
		if (package_ver > 1 && fw_info[i].dmc_id != 0)
			continue;

		if (fw_info[i].substepping == '*' &&
		    si->stepping == fw_info[i].stepping) {
			dmc_offset = fw_info[i].offset;
			break;
		}

		if (si->stepping == fw_info[i].stepping &&
		    si->substepping == fw_info[i].substepping) {
			dmc_offset = fw_info[i].offset;
			break;
		}

		if (fw_info[i].stepping == '*' &&
		    fw_info[i].substepping == '*') {
			/*
			 * In theory we should stop the search as generic
			 * entries should always come after the more specific
			 * ones, but let's continue to make sure to work even
			 * with "broken" firmwares. If we don't find a more
			 * specific one, then we use this entry
			 */
			dmc_offset = fw_info[i].offset;
		}
	}

	return dmc_offset;
}