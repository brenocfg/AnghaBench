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
struct timespec64 {int dummy; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int efx_phc_adjtime (struct ptp_clock_info*,int /*<<< orphan*/ ) ; 
 int efx_phc_gettime (struct ptp_clock_info*,struct timespec64*) ; 
 struct timespec64 timespec64_sub (struct timespec64 const,struct timespec64) ; 
 int /*<<< orphan*/  timespec64_to_ns (struct timespec64*) ; 

__attribute__((used)) static int efx_phc_settime(struct ptp_clock_info *ptp,
			   const struct timespec64 *e_ts)
{
	/* Get the current NIC time, efx_phc_gettime.
	 * Subtract from the desired time to get the offset
	 * call efx_phc_adjtime with the offset
	 */
	int rc;
	struct timespec64 time_now;
	struct timespec64 delta;

	rc = efx_phc_gettime(ptp, &time_now);
	if (rc != 0)
		return rc;

	delta = timespec64_sub(*e_ts, time_now);

	rc = efx_phc_adjtime(ptp, timespec64_to_ns(&delta));
	if (rc != 0)
		return rc;

	return 0;
}