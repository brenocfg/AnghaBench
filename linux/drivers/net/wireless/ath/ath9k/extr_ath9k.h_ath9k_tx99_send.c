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
struct sk_buff {int dummy; } ;
struct ath_tx_control {int dummy; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int ath9k_tx99_send(struct ath_softc *sc,
				  struct sk_buff *skb,
				  struct ath_tx_control *txctl)
{
	return 0;
}