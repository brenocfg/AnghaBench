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
struct bcom_task {struct bcom_gen_bd_priv* priv; int /*<<< orphan*/  flags; } ;
struct bcom_gen_bd_priv {int initiator; int ipr; int /*<<< orphan*/  fifo; } ;
struct bcom_gen_bd {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCOM_FLAGS_NONE ; 
 scalar_t__ bcom_gen_bd_tx_reset (struct bcom_task*) ; 
 struct bcom_task* bcom_task_alloc (int,int,int) ; 
 int /*<<< orphan*/  bcom_task_free (struct bcom_task*) ; 

extern struct bcom_task *
bcom_gen_bd_tx_init(int queue_len, phys_addr_t fifo,
			int initiator, int ipr)
{
	struct bcom_task *tsk;
	struct bcom_gen_bd_priv *priv;

	tsk = bcom_task_alloc(queue_len, sizeof(struct bcom_gen_bd),
			sizeof(struct bcom_gen_bd_priv));
	if (!tsk)
		return NULL;

	tsk->flags = BCOM_FLAGS_NONE;

	priv = tsk->priv;
	priv->fifo	= fifo;
	priv->initiator	= initiator;
	priv->ipr	= ipr;

	if (bcom_gen_bd_tx_reset(tsk)) {
		bcom_task_free(tsk);
		return NULL;
	}

	return tsk;
}