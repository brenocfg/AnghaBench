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

/* Variables and functions */
 unsigned int URB_NO_TRANSFER_DMA_MAP ; 

__attribute__((used)) static unsigned int tweak_transfer_flags(unsigned int flags)
{
	flags &= ~URB_NO_TRANSFER_DMA_MAP;
	return flags;
}