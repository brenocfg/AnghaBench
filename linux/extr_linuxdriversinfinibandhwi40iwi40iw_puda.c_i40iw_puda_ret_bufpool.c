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
struct i40iw_puda_rsrc {int /*<<< orphan*/  avail_buf_count; int /*<<< orphan*/  bufpool_lock; int /*<<< orphan*/  bufpool; } ;
struct i40iw_puda_buf {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void i40iw_puda_ret_bufpool(struct i40iw_puda_rsrc *rsrc,
			    struct i40iw_puda_buf *buf)
{
	unsigned long	flags;

	spin_lock_irqsave(&rsrc->bufpool_lock, flags);
	list_add(&buf->list, &rsrc->bufpool);
	spin_unlock_irqrestore(&rsrc->bufpool_lock, flags);
	rsrc->avail_buf_count++;
}