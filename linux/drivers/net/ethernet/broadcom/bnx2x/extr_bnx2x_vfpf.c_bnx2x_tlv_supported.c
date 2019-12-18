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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ CHANNEL_TLV_MAX ; 
 scalar_t__ CHANNEL_TLV_NONE ; 

bool bnx2x_tlv_supported(u16 tlvtype)
{
	return CHANNEL_TLV_NONE < tlvtype && tlvtype < CHANNEL_TLV_MAX;
}