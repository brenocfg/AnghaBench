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
struct r5l_log {int /*<<< orphan*/  last_checkpoint; TYPE_2__* rdev; } ;
struct r5conf {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {TYPE_1__* mddev; } ;
struct TYPE_3__ {struct r5conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  r5c_calculate_new_cp (struct r5conf*) ; 
 int /*<<< orphan*/  r5l_ring_distance (struct r5l_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sector_t r5l_reclaimable_space(struct r5l_log *log)
{
	struct r5conf *conf = log->rdev->mddev->private;

	return r5l_ring_distance(log, log->last_checkpoint,
				 r5c_calculate_new_cp(conf));
}