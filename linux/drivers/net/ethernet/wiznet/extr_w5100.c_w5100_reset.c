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
struct w5100_priv {int /*<<< orphan*/  ndev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* reset ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MR_PB ; 
 int /*<<< orphan*/  MR_RST ; 
 int /*<<< orphan*/  W5100_MR ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w5100_reset(struct w5100_priv *priv)
{
	if (priv->ops->reset)
		return priv->ops->reset(priv->ndev);

	w5100_write(priv, W5100_MR, MR_RST);
	mdelay(5);
	w5100_write(priv, W5100_MR, MR_PB);

	return 0;
}