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
struct TYPE_2__ {int /*<<< orphan*/  action_timestamp; } ;
struct intel_engine_cs {TYPE_1__ hangcheck; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void intel_engine_init_hangcheck(struct intel_engine_cs *engine)
{
	memset(&engine->hangcheck, 0, sizeof(engine->hangcheck));
	engine->hangcheck.action_timestamp = jiffies;
}