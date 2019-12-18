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
struct prp_priv {int /*<<< orphan*/  ic; int /*<<< orphan*/  out_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_ic_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_ic_task_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_disable_channel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prp_unsetup_norotation(struct prp_priv *priv)
{
	ipu_ic_task_disable(priv->ic);
	ipu_idmac_disable_channel(priv->out_ch);
	ipu_ic_disable(priv->ic);
}