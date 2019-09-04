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
struct nfp_fl_lag {int batch_ver; } ;

/* Variables and functions */
 int NFP_FL_LAG_VERSION_MASK ; 

__attribute__((used)) static void nfp_fl_increment_version(struct nfp_fl_lag *lag)
{
	/* LSB is not considered by firmware so add 2 for each increment. */
	lag->batch_ver += 2;
	lag->batch_ver &= NFP_FL_LAG_VERSION_MASK;

	/* Zero is reserved by firmware. */
	if (!lag->batch_ver)
		lag->batch_ver += 2;
}