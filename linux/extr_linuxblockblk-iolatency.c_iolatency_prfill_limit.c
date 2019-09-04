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
typedef  int /*<<< orphan*/  u64 ;
struct seq_file {int dummy; } ;
struct iolatency_grp {int /*<<< orphan*/  min_lat_nsec; } ;
struct blkg_policy_data {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 char* blkg_dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iolatency_grp* pd_to_lat (struct blkg_policy_data*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 iolatency_prfill_limit(struct seq_file *sf,
				  struct blkg_policy_data *pd, int off)
{
	struct iolatency_grp *iolat = pd_to_lat(pd);
	const char *dname = blkg_dev_name(pd->blkg);

	if (!dname || !iolat->min_lat_nsec)
		return 0;
	seq_printf(sf, "%s target=%llu\n",
		   dname, div_u64(iolat->min_lat_nsec, NSEC_PER_USEC));
	return 0;
}