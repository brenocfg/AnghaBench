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
struct request_queue {int dummy; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPCMD_START_STOP_UNIT ; 
 int __blk_send_generic (struct request_queue*,struct gendisk*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int blk_send_start_stop(struct request_queue *q,
				      struct gendisk *bd_disk, int data)
{
	return __blk_send_generic(q, bd_disk, GPCMD_START_STOP_UNIT, data);
}