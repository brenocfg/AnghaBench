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
struct uniphier_fi2c_priv {scalar_t__ len; scalar_t__ membase; int /*<<< orphan*/ * buf; TYPE_1__ adap; } ;

/* Variables and functions */
 scalar_t__ UNIPHIER_FI2C_DTTX ; 
 int UNIPHIER_FI2C_FIFO_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uniphier_fi2c_fill_txfifo(struct uniphier_fi2c_priv *priv,
				      bool first)
{
	int fifo_space = UNIPHIER_FI2C_FIFO_SIZE;

	/*
	 * TX-FIFO stores slave address in it for the first access.
	 * Decrement the counter.
	 */
	if (first)
		fifo_space--;

	while (priv->len) {
		if (fifo_space-- <= 0)
			break;

		dev_dbg(&priv->adap.dev, "write data: %02x\n", *priv->buf);
		writel(*priv->buf++, priv->membase + UNIPHIER_FI2C_DTTX);
		priv->len--;
	}
}