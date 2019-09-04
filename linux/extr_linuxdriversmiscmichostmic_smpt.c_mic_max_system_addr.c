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
typedef  scalar_t__ u64 ;
struct mic_device {TYPE_2__* smpt; } ;
struct TYPE_3__ {scalar_t__ base; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ mic_max_system_memory (struct mic_device*) ; 

__attribute__((used)) static inline u64 mic_max_system_addr(struct mic_device *mdev)
{
	return mdev->smpt->info.base + mic_max_system_memory(mdev) - 1ULL;
}