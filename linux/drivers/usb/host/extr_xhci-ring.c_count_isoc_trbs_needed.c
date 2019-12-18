#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct urb {TYPE_1__* iso_frame_desc; scalar_t__ transfer_dma; } ;
struct TYPE_2__ {scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 unsigned int count_trbs (scalar_t__,scalar_t__) ; 

__attribute__((used)) static unsigned int count_isoc_trbs_needed(struct urb *urb, int i)
{
	u64 addr, len;

	addr = (u64) (urb->transfer_dma + urb->iso_frame_desc[i].offset);
	len = urb->iso_frame_desc[i].length;

	return count_trbs(addr, len);
}