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
struct ath10k {int /*<<< orphan*/  napi; int /*<<< orphan*/  napi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_NAPI_BUDGET ; 
 int /*<<< orphan*/  ath10k_snoc_napi_poll ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_snoc_init_napi(struct ath10k *ar)
{
	netif_napi_add(&ar->napi_dev, &ar->napi, ath10k_snoc_napi_poll,
		       ATH10K_NAPI_BUDGET);
}