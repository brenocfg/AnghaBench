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
struct technologic_priv {int /*<<< orphan*/  io_lock; } ;
struct sja1000_priv {int /*<<< orphan*/  write_reg; int /*<<< orphan*/  read_reg; struct technologic_priv* priv; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sp_technologic_read_reg16 ; 
 int /*<<< orphan*/  sp_technologic_write_reg16 ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sp_technologic_init(struct sja1000_priv *priv, struct device_node *of)
{
	struct technologic_priv *tp = priv->priv;

	priv->read_reg = sp_technologic_read_reg16;
	priv->write_reg = sp_technologic_write_reg16;
	spin_lock_init(&tp->io_lock);

	return 0;
}