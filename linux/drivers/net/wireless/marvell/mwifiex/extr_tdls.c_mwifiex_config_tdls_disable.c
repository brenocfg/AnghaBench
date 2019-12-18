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
struct mwifiex_private {int dummy; } ;

/* Variables and functions */
 int mwifiex_config_tdls (struct mwifiex_private*,int) ; 

int mwifiex_config_tdls_disable(struct mwifiex_private *priv)
{
	return mwifiex_config_tdls(priv, false);
}