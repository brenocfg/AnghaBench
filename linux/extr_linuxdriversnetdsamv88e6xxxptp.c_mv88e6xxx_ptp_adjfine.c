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
typedef  long u64 ;
typedef  scalar_t__ u32 ;
struct ptp_clock_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ mult; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; TYPE_1__ tstamp_cc; int /*<<< orphan*/  tstamp_tc; } ;

/* Variables and functions */
 scalar_t__ CC_MULT ; 
 int /*<<< orphan*/  CC_MULT_DEM ; 
 long CC_MULT_NUM ; 
 scalar_t__ div_u64 (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mv88e6xxx_chip* ptp_to_chip (struct ptp_clock_info*) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mv88e6xxx_ptp_adjfine(struct ptp_clock_info *ptp, long scaled_ppm)
{
	struct mv88e6xxx_chip *chip = ptp_to_chip(ptp);
	int neg_adj = 0;
	u32 diff, mult;
	u64 adj;

	if (scaled_ppm < 0) {
		neg_adj = 1;
		scaled_ppm = -scaled_ppm;
	}
	mult = CC_MULT;
	adj = CC_MULT_NUM;
	adj *= scaled_ppm;
	diff = div_u64(adj, CC_MULT_DEM);

	mutex_lock(&chip->reg_lock);

	timecounter_read(&chip->tstamp_tc);
	chip->tstamp_cc.mult = neg_adj ? mult - diff : mult + diff;

	mutex_unlock(&chip->reg_lock);

	return 0;
}