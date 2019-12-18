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
struct olpc_xo175_ec {scalar_t__ logbuf_len; int /*<<< orphan*/  logbuf; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void olpc_xo175_ec_flush_logbuf(struct olpc_xo175_ec *priv)
{
	dev_dbg(&priv->spi->dev, "got debug string [%*pE]\n",
				priv->logbuf_len, priv->logbuf);
	priv->logbuf_len = 0;
}