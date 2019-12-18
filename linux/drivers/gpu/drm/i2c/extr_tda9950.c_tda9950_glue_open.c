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
struct tda9950_priv {int open; TYPE_1__* glue; } ;
struct TYPE_2__ {int (* open ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tda9950_glue_open(struct tda9950_priv *priv)
{
	int ret = 0;

	if (priv->glue && priv->glue->open)
		ret = priv->glue->open(priv->glue->data);

	priv->open = true;

	return ret;
}