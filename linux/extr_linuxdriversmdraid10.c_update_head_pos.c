#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct r10conf {TYPE_2__* mirrors; } ;
struct r10bio {scalar_t__ sectors; TYPE_3__* devs; TYPE_1__* mddev; } ;
struct TYPE_6__ {size_t devnum; scalar_t__ addr; } ;
struct TYPE_5__ {scalar_t__ head_position; } ;
struct TYPE_4__ {struct r10conf* private; } ;

/* Variables and functions */

__attribute__((used)) static inline void update_head_pos(int slot, struct r10bio *r10_bio)
{
	struct r10conf *conf = r10_bio->mddev->private;

	conf->mirrors[r10_bio->devs[slot].devnum].head_position =
		r10_bio->devs[slot].addr + (r10_bio->sectors);
}