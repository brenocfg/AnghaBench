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
struct ath10k {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int CE_COUNT ; 
 int /*<<< orphan*/  ath10k_ce_free_pipe (struct ath10k*,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_snoc_release_resource(struct ath10k *ar)
{
	int i;

	netif_napi_del(&ar->napi);
	for (i = 0; i < CE_COUNT; i++)
		ath10k_ce_free_pipe(ar, i);
}