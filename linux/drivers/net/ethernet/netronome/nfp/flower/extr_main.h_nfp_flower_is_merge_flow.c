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
struct nfp_fl_payload {unsigned long tc_flower_cookie; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfp_flower_is_merge_flow(struct nfp_fl_payload *flow_pay)
{
	return flow_pay->tc_flower_cookie == (unsigned long)flow_pay;
}