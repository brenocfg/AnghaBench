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
typedef  enum ath10k_fw_features { ____Placeholder_ath10k_fw_features } ath10k_fw_features ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 scalar_t__ ATH10K_FW_FEATURE_COUNT ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int* ath10k_core_fw_feature_str ; 
 unsigned int scnprintf (char*,size_t,char*,int) ; 

__attribute__((used)) static unsigned int ath10k_core_get_fw_feature_str(char *buf,
						   size_t buf_len,
						   enum ath10k_fw_features feat)
{
	/* make sure that ath10k_core_fw_feature_str[] gets updated */
	BUILD_BUG_ON(ARRAY_SIZE(ath10k_core_fw_feature_str) !=
		     ATH10K_FW_FEATURE_COUNT);

	if (feat >= ARRAY_SIZE(ath10k_core_fw_feature_str) ||
	    WARN_ON(!ath10k_core_fw_feature_str[feat])) {
		return scnprintf(buf, buf_len, "bit%d", feat);
	}

	return scnprintf(buf, buf_len, "%s", ath10k_core_fw_feature_str[feat]);
}