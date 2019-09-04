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
struct list_head {int dummy; } ;
struct i40iw_puda_rsrc {int /*<<< orphan*/  bufpool_lock; int /*<<< orphan*/  stats_buf_alloc_fail; int /*<<< orphan*/  avail_buf_count; struct list_head bufpool; } ;
struct i40iw_puda_buf {int dummy; } ;

/* Variables and functions */
 struct i40iw_puda_buf* i40iw_puda_get_listbuf (struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct i40iw_puda_buf *i40iw_puda_get_bufpool(struct i40iw_puda_rsrc *rsrc)
{
	struct i40iw_puda_buf *buf = NULL;
	struct list_head *list = &rsrc->bufpool;
	unsigned long	flags;

	spin_lock_irqsave(&rsrc->bufpool_lock, flags);
	buf = i40iw_puda_get_listbuf(list);
	if (buf)
		rsrc->avail_buf_count--;
	else
		rsrc->stats_buf_alloc_fail++;
	spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
	return buf;
}