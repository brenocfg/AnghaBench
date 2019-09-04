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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uniphier_fi2c_priv {int flags; scalar_t__ len; int /*<<< orphan*/ * buf; TYPE_1__ adap; scalar_t__ membase; } ;

/* Variables and functions */
 int UNIPHIER_FI2C_BYTE_WISE ; 
 scalar_t__ UNIPHIER_FI2C_DTRX ; 
 int UNIPHIER_FI2C_FIFO_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_drain_rxfifo(struct uniphier_fi2c_priv *priv)
{
	int fifo_left = priv->flags & UNIPHIER_FI2C_BYTE_WISE ?
						1 : UNIPHIER_FI2C_FIFO_SIZE;

	while (priv->len) {
		if (fifo_left-- <= 0)
			break;

		*priv->buf++ = readl(priv->membase + UNIPHIER_FI2C_DTRX);
		dev_dbg(&priv->adap.dev, "read data: %02x\n", priv->buf[-1]);
		priv->len--;
	}
}