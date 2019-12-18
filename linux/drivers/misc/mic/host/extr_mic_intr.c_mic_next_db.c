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
struct TYPE_4__ {int next_avail_src; } ;
struct mic_device {TYPE_2__ irq_info; TYPE_1__* intr_info; } ;
struct TYPE_3__ {int* intr_len; } ;

/* Variables and functions */
 size_t MIC_INTR_DB ; 

int mic_next_db(struct mic_device *mdev)
{
	int next_db;

	next_db = mdev->irq_info.next_avail_src %
		mdev->intr_info->intr_len[MIC_INTR_DB];
	mdev->irq_info.next_avail_src++;
	return next_db;
}