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
struct intel_guc_log {TYPE_1__* stats; } ;
typedef  enum guc_log_buffer_type { ____Placeholder_guc_log_buffer_type } guc_log_buffer_type ;
struct TYPE_2__ {unsigned int sampled_overflow; unsigned int overflow; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR_RATELIMITED (char*) ; 

__attribute__((used)) static bool guc_check_log_buf_overflow(struct intel_guc_log *log,
				       enum guc_log_buffer_type type,
				       unsigned int full_cnt)
{
	unsigned int prev_full_cnt = log->stats[type].sampled_overflow;
	bool overflow = false;

	if (full_cnt != prev_full_cnt) {
		overflow = true;

		log->stats[type].overflow = full_cnt;
		log->stats[type].sampled_overflow += full_cnt - prev_full_cnt;

		if (full_cnt < prev_full_cnt) {
			/* buffer_full_cnt is a 4 bit counter */
			log->stats[type].sampled_overflow += 16;
		}
		DRM_ERROR_RATELIMITED("GuC log buffer overflow\n");
	}

	return overflow;
}