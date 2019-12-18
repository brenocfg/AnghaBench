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
struct gpmc_timings {int dummy; } ;
struct gpmc_settings {scalar_t__ sync_write; scalar_t__ sync_read; scalar_t__ mux_add_data; } ;
struct gpmc_device_timings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpmc_calc_async_read_timings (struct gpmc_timings*,struct gpmc_device_timings*,int) ; 
 int /*<<< orphan*/  gpmc_calc_async_write_timings (struct gpmc_timings*,struct gpmc_device_timings*,int) ; 
 int /*<<< orphan*/  gpmc_calc_common_timings (struct gpmc_timings*,struct gpmc_device_timings*,int) ; 
 int /*<<< orphan*/  gpmc_calc_sync_read_timings (struct gpmc_timings*,struct gpmc_device_timings*,int) ; 
 int /*<<< orphan*/  gpmc_calc_sync_write_timings (struct gpmc_timings*,struct gpmc_device_timings*,int) ; 
 int /*<<< orphan*/  gpmc_convert_ps_to_ns (struct gpmc_timings*) ; 
 int /*<<< orphan*/  memset (struct gpmc_timings*,int /*<<< orphan*/ ,int) ; 

int gpmc_calc_timings(struct gpmc_timings *gpmc_t,
		      struct gpmc_settings *gpmc_s,
		      struct gpmc_device_timings *dev_t)
{
	bool mux = false, sync = false;

	if (gpmc_s) {
		mux = gpmc_s->mux_add_data ? true : false;
		sync = (gpmc_s->sync_read || gpmc_s->sync_write);
	}

	memset(gpmc_t, 0, sizeof(*gpmc_t));

	gpmc_calc_common_timings(gpmc_t, dev_t, sync);

	if (gpmc_s && gpmc_s->sync_read)
		gpmc_calc_sync_read_timings(gpmc_t, dev_t, mux);
	else
		gpmc_calc_async_read_timings(gpmc_t, dev_t, mux);

	if (gpmc_s && gpmc_s->sync_write)
		gpmc_calc_sync_write_timings(gpmc_t, dev_t, mux);
	else
		gpmc_calc_async_write_timings(gpmc_t, dev_t, mux);

	/* TODO: remove, see function definition */
	gpmc_convert_ps_to_ns(gpmc_t);

	return 0;
}