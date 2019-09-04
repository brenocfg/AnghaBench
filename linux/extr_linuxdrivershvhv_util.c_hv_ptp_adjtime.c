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
struct ptp_clock_info {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int hv_ptp_adjtime(struct ptp_clock_info *ptp, s64 delta)
{
	return -EOPNOTSUPP;
}