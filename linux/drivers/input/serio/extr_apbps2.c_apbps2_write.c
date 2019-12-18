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
 unsigned char APBPS2_CTRL_RE ; 
 unsigned char APBPS2_CTRL_RI ; 
 unsigned char APBPS2_CTRL_TE ; 
 int APBPS2_STATUS_TF ; 
 int ETIMEDOUT ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (unsigned char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int apbps2_write(struct serio *io, unsigned char val)
{
	struct apbps2_priv *priv = io->port_data;
	unsigned int tleft = 10000; /* timeout in 100ms */

	/* delay until PS/2 controller has room for more chars */
	while ((ioread32be(&priv->regs->status) & APBPS2_STATUS_TF) && tleft--)
		udelay(10);

	if ((ioread32be(&priv->regs->status) & APBPS2_STATUS_TF) == 0) {
		iowrite32be(val, &priv->regs->data);

		iowrite32be(APBPS2_CTRL_RE | APBPS2_CTRL_RI | APBPS2_CTRL_TE,
				&priv->regs->ctrl);
		return 0;
	}

	return -ETIMEDOUT;
}