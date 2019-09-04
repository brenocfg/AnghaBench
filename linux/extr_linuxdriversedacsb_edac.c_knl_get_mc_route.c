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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int GET_BITFIELD (int /*<<< orphan*/ ,int,int) ; 
 int KNL_MAX_CHANNELS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  knl_channel_remap (int,int) ; 

__attribute__((used)) static u32 knl_get_mc_route(int entry, u32 reg)
{
	int mc, chan;

	WARN_ON(entry >= KNL_MAX_CHANNELS);

	mc = GET_BITFIELD(reg, entry*3, (entry*3)+2);
	chan = GET_BITFIELD(reg, (entry*2) + 18, (entry*2) + 18 + 1);

	return knl_channel_remap(mc, chan);
}