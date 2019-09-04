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
struct cmdbuf_t {int len; struct cmdbuf_t* next; struct cmdbuf_t* prev; int /*<<< orphan*/  buf; } ;
struct cardstate {scalar_t__ mstate; int curlen; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_tasklet; scalar_t__ connected; int /*<<< orphan*/  cmdlock; struct cmdbuf_t* lastcmdbuf; int /*<<< orphan*/  cmdbytes; struct cmdbuf_t* cmdbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOCKCMD ; 
 int /*<<< orphan*/  DEBUG_TRANSCMD ; 
 scalar_t__ MS_LOCKED ; 
 int /*<<< orphan*/  gigaset_dbg_buffer (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gigaset_write_cmd(struct cardstate *cs, struct cmdbuf_t *cb)
{
	unsigned long flags;

	gigaset_dbg_buffer(cs->mstate != MS_LOCKED ?
			   DEBUG_TRANSCMD : DEBUG_LOCKCMD,
			   "CMD Transmit", cb->len, cb->buf);

	spin_lock_irqsave(&cs->cmdlock, flags);
	cb->prev = cs->lastcmdbuf;
	if (cs->lastcmdbuf)
		cs->lastcmdbuf->next = cb;
	else {
		cs->cmdbuf = cb;
		cs->curlen = cb->len;
	}
	cs->cmdbytes += cb->len;
	cs->lastcmdbuf = cb;
	spin_unlock_irqrestore(&cs->cmdlock, flags);

	spin_lock_irqsave(&cs->lock, flags);
	if (cs->connected)
		tasklet_schedule(&cs->write_tasklet);
	spin_unlock_irqrestore(&cs->lock, flags);
	return cb->len;
}