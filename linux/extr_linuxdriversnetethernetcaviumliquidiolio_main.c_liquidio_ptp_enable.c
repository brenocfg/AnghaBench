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
struct ptp_clock_request {int dummy; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
liquidio_ptp_enable(struct ptp_clock_info *ptp __attribute__((unused)),
		    struct ptp_clock_request *rq __attribute__((unused)),
		    int on __attribute__((unused)))
{
	return -EOPNOTSUPP;
}