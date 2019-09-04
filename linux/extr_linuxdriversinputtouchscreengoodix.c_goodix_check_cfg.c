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
struct goodix_ts_data {TYPE_2__* chip; TYPE_1__* client; } ;
struct firmware {scalar_t__ size; } ;
struct TYPE_4__ {int (* check_config ) (struct goodix_ts_data*,struct firmware const*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GOODIX_CONFIG_MAX_LENGTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct goodix_ts_data*,struct firmware const*) ; 

__attribute__((used)) static int goodix_check_cfg(struct goodix_ts_data *ts,
			    const struct firmware *cfg)
{
	if (cfg->size > GOODIX_CONFIG_MAX_LENGTH) {
		dev_err(&ts->client->dev,
			"The length of the config fw is not correct");
		return -EINVAL;
	}

	return ts->chip->check_config(ts, cfg);
}