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
struct at91_priv {int dummy; } ;

/* Variables and functions */
 unsigned int get_mb_rx_first (struct at91_priv const*) ; 
 unsigned int get_mb_rx_last (struct at91_priv const*) ; 

__attribute__((used)) static inline unsigned int get_mb_rx_num(const struct at91_priv *priv)
{
	return get_mb_rx_last(priv) - get_mb_rx_first(priv) + 1;
}