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
typedef  int u16 ;

/* Variables and functions */
 int ICE_MAX_NUM_DESC ; 
 int ICE_MIN_NUM_DESC ; 
 int ICE_REQ_DESC_MULTIPLE ; 

__attribute__((used)) static bool ice_vc_isvalid_ring_len(u16 ring_len)
{
	return ring_len == 0 ||
	       (ring_len >= ICE_MIN_NUM_DESC &&
		ring_len <= ICE_MAX_NUM_DESC &&
		!(ring_len % ICE_REQ_DESC_MULTIPLE));
}