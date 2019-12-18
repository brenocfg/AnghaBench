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
struct dc_link {TYPE_2__* dc; } ;
struct clock_source {int id; } ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;
struct TYPE_4__ {TYPE_1__* res_pool; } ;
struct TYPE_3__ {struct clock_source* dp_clock_source; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct clock_source*) ; 
 int CLOCK_SOURCE_ID_UNDEFINED ; 

__attribute__((used)) static enum clock_source_id get_clock_source_id(struct dc_link *link)
{
	enum clock_source_id dp_cs_id = CLOCK_SOURCE_ID_UNDEFINED;
	struct clock_source *dp_cs = link->dc->res_pool->dp_clock_source;

	if (dp_cs != NULL) {
		dp_cs_id = dp_cs->id;
	} else {
		/*
		 * dp clock source is not initialized for some reason.
		 * Should not happen, CLOCK_SOURCE_ID_EXTERNAL will be used
		 */
		ASSERT(dp_cs);
	}

	return dp_cs_id;
}