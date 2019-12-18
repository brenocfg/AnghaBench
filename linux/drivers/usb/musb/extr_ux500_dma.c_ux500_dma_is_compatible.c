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
typedef  int u32 ;
typedef  int u16 ;
struct dma_channel {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ux500_dma_is_compatible(struct dma_channel *channel,
		u16 maxpacket, void *buf, u32 length)
{
	if ((maxpacket & 0x3)		||
		((unsigned long int) buf & 0x3)	||
		(length < 512)		||
		(length & 0x3))
		return false;
	else
		return true;
}