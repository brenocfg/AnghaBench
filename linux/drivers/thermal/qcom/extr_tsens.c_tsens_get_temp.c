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
struct tsens_sensor {int /*<<< orphan*/  id; struct tsens_priv* priv; } ;
struct tsens_priv {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_temp ) (struct tsens_priv*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int stub1 (struct tsens_priv*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tsens_get_temp(void *data, int *temp)
{
	const struct tsens_sensor *s = data;
	struct tsens_priv *priv = s->priv;

	return priv->ops->get_temp(priv, s->id, temp);
}