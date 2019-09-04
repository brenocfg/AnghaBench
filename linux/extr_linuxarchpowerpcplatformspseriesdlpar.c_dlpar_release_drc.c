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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCATION_STATE ; 
 int /*<<< orphan*/  ALLOC_UNUSABLE ; 
 int DR_ENTITY_PRESENT ; 
 int /*<<< orphan*/  DR_ENTITY_SENSE ; 
 int /*<<< orphan*/  ISOLATE ; 
 int /*<<< orphan*/  ISOLATION_STATE ; 
 int /*<<< orphan*/  UNISOLATE ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rtas_set_indicator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtas_token (char*) ; 

int dlpar_release_drc(u32 drc_index)
{
	int dr_status, rc;

	rc = rtas_call(rtas_token("get-sensor-state"), 2, 2, &dr_status,
		       DR_ENTITY_SENSE, drc_index);
	if (rc || dr_status != DR_ENTITY_PRESENT)
		return -1;

	rc = rtas_set_indicator(ISOLATION_STATE, drc_index, ISOLATE);
	if (rc)
		return rc;

	rc = rtas_set_indicator(ALLOCATION_STATE, drc_index, ALLOC_UNUSABLE);
	if (rc) {
		rtas_set_indicator(ISOLATION_STATE, drc_index, UNISOLATE);
		return rc;
	}

	return 0;
}