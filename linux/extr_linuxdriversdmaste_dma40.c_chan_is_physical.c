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
struct d40_chan {scalar_t__ log_num; } ;

/* Variables and functions */
 scalar_t__ D40_PHY_CHAN ; 

__attribute__((used)) static bool chan_is_physical(struct d40_chan *chan)
{
	return chan->log_num == D40_PHY_CHAN;
}