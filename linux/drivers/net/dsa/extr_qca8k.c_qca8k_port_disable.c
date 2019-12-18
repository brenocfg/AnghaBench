#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qca8k_priv {TYPE_1__* port_sts; } ;
struct dsa_switch {scalar_t__ priv; } ;
struct TYPE_2__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  qca8k_port_set_status (struct qca8k_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca8k_port_disable(struct dsa_switch *ds, int port)
{
	struct qca8k_priv *priv = (struct qca8k_priv *)ds->priv;

	qca8k_port_set_status(priv, port, 0);
	priv->port_sts[port].enabled = 0;
}