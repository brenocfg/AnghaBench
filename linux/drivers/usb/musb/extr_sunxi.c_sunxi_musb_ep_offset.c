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
typedef  int u32 ;
typedef  scalar_t__ u16 ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 

__attribute__((used)) static u32 sunxi_musb_ep_offset(u8 epnum, u16 offset)
{
	WARN_ONCE(offset != 0,
		  "sunxi_musb_ep_offset called with non 0 offset\n");

	return 0x80; /* indexed, so ignore epnum */
}