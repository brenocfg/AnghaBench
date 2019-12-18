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
struct tape_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTBSR ; 
 int /*<<< orphan*/  MTFSF ; 
 int /*<<< orphan*/  MTFSR ; 
 int /*<<< orphan*/  MTREW ; 
 int tape_mtop (struct tape_device*,int /*<<< orphan*/ ,int) ; 

int
tape_std_mteom(struct tape_device *device, int mt_count)
{
	int rc;

	/*
	 * Seek from the beginning of tape (rewind).
	 */
	if ((rc = tape_mtop(device, MTREW, 1)) < 0)
		return rc;

	/*
	 * The logical end of volume is given by two sewuential tapemarks.
	 * Look for this by skipping to the next file (over one tapemark)
	 * and then test for another one (fsr returns 1 if a tapemark was
	 * encountered).
	 */
	do {
		if ((rc = tape_mtop(device, MTFSF, 1)) < 0)
			return rc;
		if ((rc = tape_mtop(device, MTFSR, 1)) < 0)
			return rc;
	} while (rc == 0);

	return tape_mtop(device, MTBSR, 1);
}