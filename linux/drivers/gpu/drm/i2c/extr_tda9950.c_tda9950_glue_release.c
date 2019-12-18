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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* release ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tda9950_glue_release(struct tda9950_priv *priv)
{
	priv->open = false;

	if (priv->glue && priv->glue->release)
		priv->glue->release(priv->glue->data);
}