#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int (* poll_fn ) (struct request_queue*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  blk_qc_t ;
struct TYPE_2__ {scalar_t__ plug; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_flush_plug_list (scalar_t__,int) ; 
 int /*<<< orphan*/  blk_qc_t_valid (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int stub1 (struct request_queue*,int /*<<< orphan*/ ) ; 

bool blk_poll(struct request_queue *q, blk_qc_t cookie)
{
	if (!q->poll_fn || !blk_qc_t_valid(cookie))
		return false;

	if (current->plug)
		blk_flush_plug_list(current->plug, false);
	return q->poll_fn(q, cookie);
}