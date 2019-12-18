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
typedef  size_t u8 ;

/* Variables and functions */
 size_t drm_dp_msg_data_crc4 (size_t*,size_t) ; 

__attribute__((used)) static void drm_dp_crc_sideband_chunk_req(u8 *msg, u8 len)
{
	u8 crc4;
	crc4 = drm_dp_msg_data_crc4(msg, len);
	msg[len] = crc4;
}