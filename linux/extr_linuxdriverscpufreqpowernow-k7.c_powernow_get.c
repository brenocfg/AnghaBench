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
struct TYPE_2__ {unsigned int CFID; } ;
union msr_fidvidstatus {TYPE_1__ bits; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_K7_FID_VID_STATUS ; 
 int* fid_codes ; 
 int fsb ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int powernow_get(unsigned int cpu)
{
	union msr_fidvidstatus fidvidstatus;
	unsigned int cfid;

	if (cpu)
		return 0;
	rdmsrl(MSR_K7_FID_VID_STATUS, fidvidstatus.val);
	cfid = fidvidstatus.bits.CFID;

	return fsb * fid_codes[cfid] / 10;
}