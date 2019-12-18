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
struct tg3 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_napi_disable (struct tg3*) ; 

__attribute__((used)) static inline void tg3_netif_stop(struct tg3 *tp)
{
	netif_trans_update(tp->dev);	/* prevent tx timeout */
	tg3_napi_disable(tp);
	netif_carrier_off(tp->dev);
	netif_tx_disable(tp->dev);
}