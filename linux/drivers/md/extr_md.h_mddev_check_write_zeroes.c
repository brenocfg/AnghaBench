#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mddev {TYPE_5__* queue; } ;
struct bio {TYPE_3__* bi_disk; } ;
struct TYPE_9__ {scalar_t__ max_write_zeroes_sectors; } ;
struct TYPE_10__ {TYPE_4__ limits; } ;
struct TYPE_8__ {TYPE_2__* queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_write_zeroes_sectors; } ;
struct TYPE_7__ {TYPE_1__ limits; } ;

/* Variables and functions */
 scalar_t__ REQ_OP_WRITE_ZEROES ; 
 scalar_t__ bio_op (struct bio*) ; 

__attribute__((used)) static inline void mddev_check_write_zeroes(struct mddev *mddev, struct bio *bio)
{
	if (bio_op(bio) == REQ_OP_WRITE_ZEROES &&
	    !bio->bi_disk->queue->limits.max_write_zeroes_sectors)
		mddev->queue->limits.max_write_zeroes_sectors = 0;
}