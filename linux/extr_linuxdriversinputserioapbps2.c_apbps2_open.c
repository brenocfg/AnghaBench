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
struct serio {struct apbps2_priv* port_data; } ;
struct apbps2_priv {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; int /*<<< orphan*/  data; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int APBPS2_CTRL_RE ; 
 int APBPS2_CTRL_RI ; 
 unsigned long APBPS2_STATUS_DR ; 
 unsigned long ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apbps2_open(struct serio *io)
{
	struct apbps2_priv *priv = io->port_data;
	int limit;
	unsigned long tmp;

	/* clear error flags */
	iowrite32be(0, &priv->regs->status);

	/* Clear old data if available (unlikely) */
	limit = 1024;
	while ((ioread32be(&priv->regs->status) & APBPS2_STATUS_DR) && --limit)
		tmp = ioread32be(&priv->regs->data);

	/* Enable reciever and it's interrupt */
	iowrite32be(APBPS2_CTRL_RE | APBPS2_CTRL_RI, &priv->regs->ctrl);

	return 0;
}