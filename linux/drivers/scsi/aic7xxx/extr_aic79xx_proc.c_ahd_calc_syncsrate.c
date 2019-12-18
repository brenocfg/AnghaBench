#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ period_factor; int period; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* scsi_syncrates ; 

__attribute__((used)) static u_int
ahd_calc_syncsrate(u_int period_factor)
{
	int i;

	/* See if the period is in the "exception" table */
	for (i = 0; i < ARRAY_SIZE(scsi_syncrates); i++) {

		if (period_factor == scsi_syncrates[i].period_factor) {
			/* Period in kHz */
			return (100000000 / scsi_syncrates[i].period);
		}
	}

	/*
	 * Wasn't in the table, so use the standard
	 * 4 times conversion.
	 */
	return (10000000 / (period_factor * 4 * 10));
}