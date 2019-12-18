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
struct cmdbuf_t {scalar_t__ wake_tasklet; scalar_t__ len; int /*<<< orphan*/ * prev; struct cmdbuf_t* next; } ;
struct cardstate {scalar_t__ curlen; int /*<<< orphan*/ * lastcmdbuf; struct cmdbuf_t* cmdbuf; int /*<<< orphan*/  cmdbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmdbuf_t*) ; 
 int /*<<< orphan*/  tasklet_schedule (scalar_t__) ; 

__attribute__((used)) static void complete_cb(struct cardstate *cs)
{
	struct cmdbuf_t *cb = cs->cmdbuf;

	/* unqueue completed buffer */
	cs->cmdbytes -= cs->curlen;
	gig_dbg(DEBUG_OUTPUT, "write_command: sent %u bytes, %u left",
		cs->curlen, cs->cmdbytes);
	if (cb->next != NULL) {
		cs->cmdbuf = cb->next;
		cs->cmdbuf->prev = NULL;
		cs->curlen = cs->cmdbuf->len;
	} else {
		cs->cmdbuf = NULL;
		cs->lastcmdbuf = NULL;
		cs->curlen = 0;
	}

	if (cb->wake_tasklet)
		tasklet_schedule(cb->wake_tasklet);

	kfree(cb);
}