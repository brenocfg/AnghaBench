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
struct ath10k_fw_crash_data {int /*<<< orphan*/  ramdump_buf; int /*<<< orphan*/  ramdump_buf_len; } ;
struct TYPE_2__ {struct ath10k_fw_crash_data* fw_crash_data; } ;
struct ath10k {TYPE_1__ coredump; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_CRASH_DUMP_RAM_DATA ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ath10k_coredump_get_ramdump_size (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_coredump_mask ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

int ath10k_coredump_register(struct ath10k *ar)
{
	struct ath10k_fw_crash_data *crash_data = ar->coredump.fw_crash_data;

	if (test_bit(ATH10K_FW_CRASH_DUMP_RAM_DATA, &ath10k_coredump_mask)) {
		crash_data->ramdump_buf_len = ath10k_coredump_get_ramdump_size(ar);

		crash_data->ramdump_buf = vzalloc(crash_data->ramdump_buf_len);
		if (!crash_data->ramdump_buf)
			return -ENOMEM;
	}

	return 0;
}