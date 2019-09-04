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
typedef  enum latency_range { ____Placeholder_latency_range } latency_range ;

/* Variables and functions */
 int IGBVF_20K_ITR ; 
 int IGBVF_4K_ITR ; 
 int IGBVF_70K_ITR ; 
 int IGBVF_START_ITR ; 
#define  bulk_latency 130 
#define  low_latency 129 
#define  lowest_latency 128 

__attribute__((used)) static int igbvf_range_to_itr(enum latency_range current_range)
{
	int new_itr;

	switch (current_range) {
	/* counts and packets in update_itr are dependent on these numbers */
	case lowest_latency:
		new_itr = IGBVF_70K_ITR;
		break;
	case low_latency:
		new_itr = IGBVF_20K_ITR;
		break;
	case bulk_latency:
		new_itr = IGBVF_4K_ITR;
		break;
	default:
		new_itr = IGBVF_START_ITR;
		break;
	}
	return new_itr;
}