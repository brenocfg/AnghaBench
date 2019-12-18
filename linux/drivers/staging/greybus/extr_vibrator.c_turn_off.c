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
struct gb_vibrator_device {TYPE_1__* connection; } ;
struct gb_bundle {int dummy; } ;
struct TYPE_2__ {struct gb_bundle* bundle; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_VIBRATOR_TYPE_OFF ; 
 int gb_operation_sync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 

__attribute__((used)) static int turn_off(struct gb_vibrator_device *vib)
{
	struct gb_bundle *bundle = vib->connection->bundle;
	int ret;

	ret = gb_operation_sync(vib->connection, GB_VIBRATOR_TYPE_OFF,
				NULL, 0, NULL, 0);

	gb_pm_runtime_put_autosuspend(bundle);

	return ret;
}