#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_5__ {int nr_chans; int /*<<< orphan*/  name; int /*<<< orphan*/  unlink; int /*<<< orphan*/  link; } ;
struct TYPE_6__ {TYPE_1__ data; TYPE_4__ hrtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int STM_HEARTBEAT_MAX ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int nr_devs ; 
 TYPE_3__* stm_heartbeat ; 
 int /*<<< orphan*/  stm_heartbeat_hrtimer_handler ; 
 int /*<<< orphan*/  stm_heartbeat_link ; 
 int /*<<< orphan*/  stm_heartbeat_unlink ; 
 int stm_source_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stm_source_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static int stm_heartbeat_init(void)
{
	int i, ret = -ENOMEM;

	if (nr_devs < 0 || nr_devs > STM_HEARTBEAT_MAX)
		return -EINVAL;

	for (i = 0; i < nr_devs; i++) {
		stm_heartbeat[i].data.name =
			kasprintf(GFP_KERNEL, "heartbeat.%d", i);
		if (!stm_heartbeat[i].data.name)
			goto fail_unregister;

		stm_heartbeat[i].data.nr_chans	= 1;
		stm_heartbeat[i].data.link	= stm_heartbeat_link;
		stm_heartbeat[i].data.unlink	= stm_heartbeat_unlink;
		hrtimer_init(&stm_heartbeat[i].hrtimer, CLOCK_MONOTONIC,
			     HRTIMER_MODE_ABS);
		stm_heartbeat[i].hrtimer.function =
			stm_heartbeat_hrtimer_handler;

		ret = stm_source_register_device(NULL, &stm_heartbeat[i].data);
		if (ret)
			goto fail_free;
	}

	return 0;

fail_unregister:
	for (i--; i >= 0; i--) {
		stm_source_unregister_device(&stm_heartbeat[i].data);
fail_free:
		kfree(stm_heartbeat[i].data.name);
	}

	return ret;
}