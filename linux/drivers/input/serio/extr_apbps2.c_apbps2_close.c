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
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void apbps2_close(struct serio *io)
{
	struct apbps2_priv *priv = io->port_data;

	/* stop interrupts at PS/2 HW level */
	iowrite32be(0, &priv->regs->ctrl);
}