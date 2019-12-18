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
struct platform_device {int dummy; } ;
struct logger_data {int /*<<< orphan*/  log_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 struct logger_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cros_usbpd_logger_remove(struct platform_device *pd)
{
	struct logger_data *logger = platform_get_drvdata(pd);

	cancel_delayed_work_sync(&logger->log_work);

	return 0;
}