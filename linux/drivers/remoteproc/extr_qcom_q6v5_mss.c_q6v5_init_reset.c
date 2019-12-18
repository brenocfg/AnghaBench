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
struct q6v5 {void* pdc_reset; int /*<<< orphan*/  dev; scalar_t__ has_alt_reset; void* mss_restart; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_reset_control_get_exclusive (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int q6v5_init_reset(struct q6v5 *qproc)
{
	qproc->mss_restart = devm_reset_control_get_exclusive(qproc->dev,
							      "mss_restart");
	if (IS_ERR(qproc->mss_restart)) {
		dev_err(qproc->dev, "failed to acquire mss restart\n");
		return PTR_ERR(qproc->mss_restart);
	}

	if (qproc->has_alt_reset) {
		qproc->pdc_reset = devm_reset_control_get_exclusive(qproc->dev,
								    "pdc_reset");
		if (IS_ERR(qproc->pdc_reset)) {
			dev_err(qproc->dev, "failed to acquire pdc reset\n");
			return PTR_ERR(qproc->pdc_reset);
		}
	}

	return 0;
}