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
typedef  int const u32 ;

/* Variables and functions */

__attribute__((used)) static inline u32 sunxi_nfc_buf_to_user_data(const u8 *buf)
{
	return buf[0] | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}