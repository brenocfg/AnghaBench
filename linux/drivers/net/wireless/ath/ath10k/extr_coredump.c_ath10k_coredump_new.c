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
struct ath10k_fw_crash_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  guid; } ;
struct TYPE_2__ {struct ath10k_fw_crash_data* fw_crash_data; } ;
struct ath10k {int /*<<< orphan*/  dump_mutex; TYPE_1__ coredump; } ;

/* Variables and functions */
 scalar_t__ ath10k_coredump_mask ; 
 int /*<<< orphan*/  guid_gen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct ath10k_fw_crash_data *ath10k_coredump_new(struct ath10k *ar)
{
	struct ath10k_fw_crash_data *crash_data = ar->coredump.fw_crash_data;

	lockdep_assert_held(&ar->dump_mutex);

	if (ath10k_coredump_mask == 0)
		/* coredump disabled */
		return NULL;

	guid_gen(&crash_data->guid);
	ktime_get_real_ts64(&crash_data->timestamp);

	return crash_data;
}