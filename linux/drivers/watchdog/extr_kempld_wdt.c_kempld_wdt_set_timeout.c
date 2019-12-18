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
struct watchdog_device {unsigned int timeout; } ;
struct kempld_wdt_stage {scalar_t__ mask; } ;
struct kempld_wdt_data {unsigned int pretimeout; struct kempld_wdt_stage* stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTION_RESET ; 
 size_t STAGE_PRETIMEOUT ; 
 size_t STAGE_TIMEOUT ; 
 int kempld_wdt_set_stage_action (struct kempld_wdt_data*,struct kempld_wdt_stage*,int /*<<< orphan*/ ) ; 
 int kempld_wdt_set_stage_timeout (struct kempld_wdt_data*,struct kempld_wdt_stage*,unsigned int) ; 
 struct kempld_wdt_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int kempld_wdt_set_timeout(struct watchdog_device *wdd,
					unsigned int timeout)
{
	struct kempld_wdt_data *wdt_data = watchdog_get_drvdata(wdd);
	struct kempld_wdt_stage *pretimeout_stage;
	struct kempld_wdt_stage *timeout_stage;
	int ret;

	timeout_stage = &wdt_data->stage[STAGE_TIMEOUT];
	pretimeout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];

	if (pretimeout_stage->mask && wdt_data->pretimeout > 0)
		timeout = wdt_data->pretimeout;

	ret = kempld_wdt_set_stage_action(wdt_data, timeout_stage,
						ACTION_RESET);
	if (ret)
		return ret;
	ret = kempld_wdt_set_stage_timeout(wdt_data, timeout_stage,
						timeout);
	if (ret)
		return ret;

	wdd->timeout = timeout;
	return 0;
}