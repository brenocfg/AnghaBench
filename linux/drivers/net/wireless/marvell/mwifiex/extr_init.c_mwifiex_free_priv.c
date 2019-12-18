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
 int /*<<< orphan*/  mwifiex_clean_txrx (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_delete_bss_prio_tbl (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_free_curr_bcn (struct mwifiex_private*) ; 

void mwifiex_free_priv(struct mwifiex_private *priv)
{
	mwifiex_clean_txrx(priv);
	mwifiex_delete_bss_prio_tbl(priv);
	mwifiex_free_curr_bcn(priv);
}