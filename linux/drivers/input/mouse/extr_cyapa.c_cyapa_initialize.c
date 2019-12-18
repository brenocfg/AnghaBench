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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct cyapa {TYPE_1__* ops; scalar_t__ operational; int /*<<< orphan*/  suspend_power_mode; int /*<<< orphan*/  suspend_sleep_time; int /*<<< orphan*/  state_sync_lock; int /*<<< orphan*/  gen; int /*<<< orphan*/  state; } ;
struct TYPE_8__ {int (* initialize ) (struct cyapa*) ;} ;
struct TYPE_7__ {int (* initialize ) (struct cyapa*) ;} ;
struct TYPE_6__ {int (* initialize ) (struct cyapa*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_power_mode ) (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_GEN_UNKNOWN ; 
 int /*<<< orphan*/  CYAPA_PM_ACTIVE ; 
 int /*<<< orphan*/  CYAPA_STATE_NO_DEVICE ; 
 int /*<<< orphan*/  PWR_MODE_OFF ; 
 int /*<<< orphan*/  PWR_MODE_SLEEP ; 
 int cyapa_detect (struct cyapa*) ; 
 TYPE_4__ cyapa_gen3_ops ; 
 TYPE_3__ cyapa_gen5_ops ; 
 TYPE_2__ cyapa_gen6_ops ; 
 int /*<<< orphan*/  cyapa_pwr_cmd_to_sleep_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct cyapa*) ; 
 int stub2 (struct cyapa*) ; 
 int stub3 (struct cyapa*) ; 
 int /*<<< orphan*/  stub4 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyapa_initialize(struct cyapa *cyapa)
{
	int error = 0;

	cyapa->state = CYAPA_STATE_NO_DEVICE;
	cyapa->gen = CYAPA_GEN_UNKNOWN;
	mutex_init(&cyapa->state_sync_lock);

	/*
	 * Set to hard code default, they will be updated with trackpad set
	 * default values after probe and initialized.
	 */
	cyapa->suspend_power_mode = PWR_MODE_SLEEP;
	cyapa->suspend_sleep_time =
		cyapa_pwr_cmd_to_sleep_time(cyapa->suspend_power_mode);

	/* ops.initialize() is aimed to prepare for module communications. */
	error = cyapa_gen3_ops.initialize(cyapa);
	if (!error)
		error = cyapa_gen5_ops.initialize(cyapa);
	if (!error)
		error = cyapa_gen6_ops.initialize(cyapa);
	if (error)
		return error;

	error = cyapa_detect(cyapa);
	if (error)
		return error;

	/* Power down the device until we need it. */
	if (cyapa->operational)
		cyapa->ops->set_power_mode(cyapa,
				PWR_MODE_OFF, 0, CYAPA_PM_ACTIVE);

	return 0;
}