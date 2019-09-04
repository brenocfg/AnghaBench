#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct omap3isp_stat_data_time32 {int /*<<< orphan*/  buf; TYPE_1__ ts; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct omap3isp_stat_data {int /*<<< orphan*/  buf; TYPE_2__ ts; } ;
struct ispstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int omap3isp_stat_request_statistics (struct ispstat*,struct omap3isp_stat_data*) ; 

int omap3isp_stat_request_statistics_time32(struct ispstat *stat,
					struct omap3isp_stat_data_time32 *data)
{
	struct omap3isp_stat_data data64;
	int ret;

	ret = omap3isp_stat_request_statistics(stat, &data64);
	if (ret)
		return ret;

	data->ts.tv_sec = data64.ts.tv_sec;
	data->ts.tv_usec = data64.ts.tv_usec;
	memcpy(&data->buf, &data64.buf, sizeof(*data) - sizeof(data->ts));

	return 0;
}