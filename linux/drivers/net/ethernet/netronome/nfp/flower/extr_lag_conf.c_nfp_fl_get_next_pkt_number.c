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
struct nfp_fl_lag {unsigned int pkt_num; } ;

/* Variables and functions */
 unsigned int NFP_FL_LAG_PKT_NUMBER_MASK ; 

__attribute__((used)) static unsigned int nfp_fl_get_next_pkt_number(struct nfp_fl_lag *lag)
{
	lag->pkt_num++;
	lag->pkt_num &= NFP_FL_LAG_PKT_NUMBER_MASK;

	return lag->pkt_num;
}