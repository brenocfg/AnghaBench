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
struct imx_mu_con_priv {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbox_chan_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx_mu_txdb_tasklet(unsigned long data)
{
	struct imx_mu_con_priv *cp = (struct imx_mu_con_priv *)data;

	mbox_chan_txdone(cp->chan, 0);
}