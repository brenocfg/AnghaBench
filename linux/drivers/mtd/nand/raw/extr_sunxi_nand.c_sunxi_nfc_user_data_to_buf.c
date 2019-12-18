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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static inline void sunxi_nfc_user_data_to_buf(u32 user_data, u8 *buf)
{
	buf[0] = user_data;
	buf[1] = user_data >> 8;
	buf[2] = user_data >> 16;
	buf[3] = user_data >> 24;
}