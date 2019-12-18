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
struct alx_priv {int num_napi; struct alx_napi** qnapi; } ;
struct alx_napi {struct alx_napi* rxq; struct alx_napi* txq; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct alx_napi*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alx_free_napis(struct alx_priv *alx)
{
	struct alx_napi *np;
	int i;

	for (i = 0; i < alx->num_napi; i++) {
		np = alx->qnapi[i];
		if (!np)
			continue;

		netif_napi_del(&np->napi);
		kfree(np->txq);
		kfree(np->rxq);
		kfree(np);
		alx->qnapi[i] = NULL;
	}
}