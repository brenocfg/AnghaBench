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
struct watchdog_device {int dummy; } ;
struct fts_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_WATCHDOG_TIME_PRESET ; 
 int fts_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fts_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int fts_wd_stop(struct watchdog_device *wdd)
{
	struct fts_data *data;

	data = watchdog_get_drvdata(wdd);
	return fts_write_byte(data->client, FTS_WATCHDOG_TIME_PRESET, 0);
}