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
struct channel_program {int dummy; } ;
struct ccwchain {struct ccw1* ch_ccw; } ;
struct ccw1 {int dummy; } ;

/* Variables and functions */
 scalar_t__ ccw_is_tic (struct ccw1*) ; 
 int ccwchain_fetch_direct (struct ccwchain*,int,struct channel_program*) ; 
 int ccwchain_fetch_tic (struct ccwchain*,int,struct channel_program*) ; 

__attribute__((used)) static int ccwchain_fetch_one(struct ccwchain *chain,
			      int idx,
			      struct channel_program *cp)
{
	struct ccw1 *ccw = chain->ch_ccw + idx;

	if (ccw_is_tic(ccw))
		return ccwchain_fetch_tic(chain, idx, cp);

	return ccwchain_fetch_direct(chain, idx, cp);
}