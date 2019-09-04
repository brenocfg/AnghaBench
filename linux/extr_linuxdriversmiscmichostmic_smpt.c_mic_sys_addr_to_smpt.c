#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct mic_device {TYPE_2__* smpt; } ;
typedef  int dma_addr_t ;
struct TYPE_3__ {int base; int page_shift; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 mic_sys_addr_to_smpt(struct mic_device *mdev, dma_addr_t pa)
{
	return (pa - mdev->smpt->info.base) >> mdev->smpt->info.page_shift;
}