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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MAXVAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PACKET_SIZE ; 

__attribute__((used)) static u32 bnx2x_ets_get_credit_upper_bound(const u32 min_w_val)
{
	const u32 credit_upper_bound = (u32)MAXVAL((150 * min_w_val),
						MAX_PACKET_SIZE);
	return credit_upper_bound;
}