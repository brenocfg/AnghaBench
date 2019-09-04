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
typedef  int u8 ;
typedef  scalar_t__ MPT_DRIVER_CLASS ;

/* Variables and functions */
 int MPT_MAX_PROTOCOL_DRIVERS ; 
 scalar_t__* MptDriverClass ; 

__attribute__((used)) static u8
mpt_get_cb_idx(MPT_DRIVER_CLASS dclass)
{
	u8 cb_idx;

	for (cb_idx = MPT_MAX_PROTOCOL_DRIVERS-1; cb_idx; cb_idx--)
		if (MptDriverClass[cb_idx] == dclass)
			return cb_idx;
	return 0;
}