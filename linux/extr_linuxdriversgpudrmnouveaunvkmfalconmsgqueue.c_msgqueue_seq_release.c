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
struct nvkm_msgqueue_seq {int /*<<< orphan*/  id; int /*<<< orphan*/ * completion; int /*<<< orphan*/ * callback; int /*<<< orphan*/  state; } ;
struct nvkm_msgqueue {int /*<<< orphan*/  seq_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_STATE_FREE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msgqueue_seq_release(struct nvkm_msgqueue *priv, struct nvkm_msgqueue_seq *seq)
{
	/* no need to acquire seq_lock since clear_bit is atomic */
	seq->state = SEQ_STATE_FREE;
	seq->callback = NULL;
	seq->completion = NULL;
	clear_bit(seq->id, priv->seq_tbl);
}