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
struct request_queue {int /*<<< orphan*/  queue_tags; } ;
struct request {int dummy; } ;

/* Variables and functions */
 struct request* blk_map_queue_find_tag (int /*<<< orphan*/ ,int) ; 

struct request *blk_queue_find_tag(struct request_queue *q, int tag)
{
	return blk_map_queue_find_tag(q->queue_tags, tag);
}