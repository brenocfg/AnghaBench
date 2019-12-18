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
struct TYPE_2__ {int /*<<< orphan*/  emit_config_values; int /*<<< orphan*/  set_config_value; int /*<<< orphan*/  allow_migrations; int /*<<< orphan*/  tick; int /*<<< orphan*/  residency; int /*<<< orphan*/  get_hint; int /*<<< orphan*/  invalidate_mapping; int /*<<< orphan*/  load_mapping; int /*<<< orphan*/  clear_dirty; int /*<<< orphan*/  set_dirty; int /*<<< orphan*/  complete_background_work; int /*<<< orphan*/  get_background_work; int /*<<< orphan*/  lookup_with_work; int /*<<< orphan*/  lookup; int /*<<< orphan*/  destroy; } ;
struct smq_policy {TYPE_1__ policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mq_emit_config_values ; 
 int /*<<< orphan*/  mq_set_config_value ; 
 int /*<<< orphan*/  smq_allow_migrations ; 
 int /*<<< orphan*/  smq_clear_dirty ; 
 int /*<<< orphan*/  smq_complete_background_work ; 
 int /*<<< orphan*/  smq_destroy ; 
 int /*<<< orphan*/  smq_get_background_work ; 
 int /*<<< orphan*/  smq_get_hint ; 
 int /*<<< orphan*/  smq_invalidate_mapping ; 
 int /*<<< orphan*/  smq_load_mapping ; 
 int /*<<< orphan*/  smq_lookup ; 
 int /*<<< orphan*/  smq_lookup_with_work ; 
 int /*<<< orphan*/  smq_residency ; 
 int /*<<< orphan*/  smq_set_dirty ; 
 int /*<<< orphan*/  smq_tick ; 

__attribute__((used)) static void init_policy_functions(struct smq_policy *mq, bool mimic_mq)
{
	mq->policy.destroy = smq_destroy;
	mq->policy.lookup = smq_lookup;
	mq->policy.lookup_with_work = smq_lookup_with_work;
	mq->policy.get_background_work = smq_get_background_work;
	mq->policy.complete_background_work = smq_complete_background_work;
	mq->policy.set_dirty = smq_set_dirty;
	mq->policy.clear_dirty = smq_clear_dirty;
	mq->policy.load_mapping = smq_load_mapping;
	mq->policy.invalidate_mapping = smq_invalidate_mapping;
	mq->policy.get_hint = smq_get_hint;
	mq->policy.residency = smq_residency;
	mq->policy.tick = smq_tick;
	mq->policy.allow_migrations = smq_allow_migrations;

	if (mimic_mq) {
		mq->policy.set_config_value = mq_set_config_value;
		mq->policy.emit_config_values = mq_emit_config_values;
	}
}