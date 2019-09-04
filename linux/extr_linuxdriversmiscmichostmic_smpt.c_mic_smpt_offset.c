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
typedef  int u64 ;
struct mic_device {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int mic_system_page_mask (struct mic_device*) ; 

__attribute__((used)) static inline u64 mic_smpt_offset(struct mic_device *mdev, dma_addr_t pa)
{
	return pa & mic_system_page_mask(mdev);
}