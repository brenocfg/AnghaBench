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
struct peak_canfd_priv {scalar_t__ cmd_len; } ;

/* Variables and functions */

__attribute__((used)) static struct peak_canfd_priv *pucan_init_cmd(struct peak_canfd_priv *priv)
{
	priv->cmd_len = 0;
	return priv;
}