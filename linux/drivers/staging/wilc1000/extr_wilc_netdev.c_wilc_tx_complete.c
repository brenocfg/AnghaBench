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
struct tx_complete_data {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct tx_complete_data*) ; 

__attribute__((used)) static void wilc_tx_complete(void *priv, int status)
{
	struct tx_complete_data *pv_data = priv;

	dev_kfree_skb(pv_data->skb);
	kfree(pv_data);
}