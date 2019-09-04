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
struct alx_priv {int num_txq; TYPE_1__** qnapi; } ;
struct TYPE_2__ {scalar_t__ rxq; scalar_t__ txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  alx_free_rxring_buf (scalar_t__) ; 
 int /*<<< orphan*/  alx_free_txring_buf (scalar_t__) ; 

__attribute__((used)) static void alx_free_buffers(struct alx_priv *alx)
{
	int i;

	for (i = 0; i < alx->num_txq; i++)
		if (alx->qnapi[i] && alx->qnapi[i]->txq)
			alx_free_txring_buf(alx->qnapi[i]->txq);

	if (alx->qnapi[0] && alx->qnapi[0]->rxq)
		alx_free_rxring_buf(alx->qnapi[0]->rxq);
}