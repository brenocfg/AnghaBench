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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dc_link {TYPE_4__* ctx; TYPE_2__* link_enc; } ;
struct TYPE_8__ {int /*<<< orphan*/  logger; } ;
struct TYPE_7__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {int (* is_in_alt_mode ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOGGER_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_LOG_WARNING (char*,int) ; 
 int div_u64 (unsigned long long,int) ; 
 unsigned long long dm_get_elapse_time_in_ns (TYPE_4__*,unsigned long long,unsigned long long) ; 
 unsigned long long dm_get_timestamp (TYPE_4__*) ; 
 int stub1 (TYPE_2__*) ; 
 int stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  udelay (unsigned int) ; 

bool wait_for_alt_mode(struct dc_link *link)
{

	/**
	 * something is terribly wrong if time out is > 200ms. (5Hz)
	 * 500 microseconds * 400 tries us 200 ms
	 **/
	unsigned int sleep_time_in_microseconds = 500;
	unsigned int tries_allowed = 400;
	bool is_in_alt_mode;
	unsigned long long enter_timestamp;
	unsigned long long finish_timestamp;
	unsigned long long time_taken_in_ns;
	int tries_taken;

	DC_LOGGER_INIT(link->ctx->logger);

	if (link->link_enc->funcs->is_in_alt_mode == NULL)
		return true;

	is_in_alt_mode = link->link_enc->funcs->is_in_alt_mode(link->link_enc);
	DC_LOG_WARNING("DP Alt mode state on HPD: %d\n", is_in_alt_mode);

	if (is_in_alt_mode)
		return true;

	enter_timestamp = dm_get_timestamp(link->ctx);

	for (tries_taken = 0; tries_taken < tries_allowed; tries_taken++) {
		udelay(sleep_time_in_microseconds);
		/* ask the link if alt mode is enabled, if so return ok */
		if (link->link_enc->funcs->is_in_alt_mode(link->link_enc)) {

			finish_timestamp = dm_get_timestamp(link->ctx);
			time_taken_in_ns = dm_get_elapse_time_in_ns(
				link->ctx, finish_timestamp, enter_timestamp);
			DC_LOG_WARNING("Alt mode entered finished after %llu ms\n",
				       div_u64(time_taken_in_ns, 1000000));
			return true;
		}

	}
	finish_timestamp = dm_get_timestamp(link->ctx);
	time_taken_in_ns = dm_get_elapse_time_in_ns(link->ctx, finish_timestamp,
						    enter_timestamp);
	DC_LOG_WARNING("Alt mode has timed out after %llu ms\n",
			div_u64(time_taken_in_ns, 1000000));
	return false;
}