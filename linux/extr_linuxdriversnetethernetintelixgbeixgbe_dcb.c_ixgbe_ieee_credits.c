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
typedef  int /*<<< orphan*/  s32 ;
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int DCB_CREDIT_QUANTUM ; 
 int MAX_CREDIT ; 
 int /*<<< orphan*/  MAX_CREDIT_REFILL ; 
 int MAX_TRAFFIC_CLASS ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 ixgbe_ieee_credits(__u8 *bw, __u16 *refill,
			      __u16 *max, int max_frame)
{
	int min_percent = 100;
	int min_credit, multiplier;
	int i;

	min_credit = ((max_frame / 2) + DCB_CREDIT_QUANTUM - 1) /
			DCB_CREDIT_QUANTUM;

	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		if (bw[i] < min_percent && bw[i])
			min_percent = bw[i];
	}

	multiplier = (min_credit / min_percent) + 1;

	/* Find out the hw credits for each TC */
	for (i = 0; i < MAX_TRAFFIC_CLASS; i++) {
		int val = min(bw[i] * multiplier, MAX_CREDIT_REFILL);

		if (val < min_credit)
			val = min_credit;
		refill[i] = val;

		max[i] = bw[i] ? (bw[i] * MAX_CREDIT)/100 : min_credit;
	}
	return 0;
}