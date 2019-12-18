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
typedef  int /*<<< orphan*/  u64 ;
struct nvkm_timer_wait {scalar_t__ reads; int /*<<< orphan*/  limit; int /*<<< orphan*/  tmr; } ;
struct nvkm_device {int /*<<< orphan*/  timer; } ;

/* Variables and functions */

void
nvkm_timer_wait_init(struct nvkm_device *device, u64 nsec,
		     struct nvkm_timer_wait *wait)
{
	wait->tmr = device->timer;
	wait->limit = nsec;
	wait->reads = 0;
}