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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ WILC_MAX_CFG_FRAME_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  put_unaligned_le16 (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wilc_wlan_cfg_set_str(u8 *frame, u32 offset, u16 id, u8 *str,
				 u32 size)
{
	if ((offset + size + 4) >= WILC_MAX_CFG_FRAME_SIZE)
		return 0;

	put_unaligned_le16(id, &frame[offset]);
	put_unaligned_le16(size, &frame[offset + 2]);
	if (str && size != 0)
		memcpy(&frame[offset + 4], str, size);

	return (size + 4);
}