#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_guc_log {TYPE_3__* stats; } ;
typedef  enum guc_log_buffer_type { ____Placeholder_guc_log_buffer_type } guc_log_buffer_type ;
struct TYPE_8__ {TYPE_2__* i915; } ;
struct TYPE_7__ {unsigned int sampled_overflow; unsigned int overflow; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_notice_ratelimited (int /*<<< orphan*/ ,char*) ; 
 TYPE_4__* guc_to_gt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_to_guc (struct intel_guc_log*) ; 

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

		dev_notice_ratelimited(guc_to_gt(log_to_guc(log))->i915->drm.dev,
				       "GuC log buffer overflow\n");
	}

	return overflow;
}