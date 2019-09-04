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
struct ftgmac100 {int rx_q_entries; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ftgmac100_next_rx_pointer(struct ftgmac100 *priv,
					      unsigned int pointer)
{
	return (pointer + 1) & (priv->rx_q_entries - 1);
}