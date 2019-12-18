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
typedef  int /*<<< orphan*/  u32 ;
struct at91_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_TCR ; 
 int /*<<< orphan*/  at91_write (struct at91_priv const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mb_rx_low_mask (struct at91_priv const*) ; 

__attribute__((used)) static inline void at91_activate_rx_low(const struct at91_priv *priv)
{
	u32 mask = get_mb_rx_low_mask(priv);
	at91_write(priv, AT91_TCR, mask);
}