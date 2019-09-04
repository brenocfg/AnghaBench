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
struct uniphier_system_bus_priv {int /*<<< orphan*/  dev; TYPE_1__* bank; } ;
struct TYPE_2__ {scalar_t__ end; scalar_t__ base; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int uniphier_system_bus_check_overlap(
				const struct uniphier_system_bus_priv *priv)
{
	int i, j;

	for (i = 0; i < ARRAY_SIZE(priv->bank); i++) {
		for (j = i + 1; j < ARRAY_SIZE(priv->bank); j++) {
			if (priv->bank[i].end > priv->bank[j].base &&
			    priv->bank[i].base < priv->bank[j].end) {
				dev_err(priv->dev,
					"region overlap between bank%d and bank%d\n",
					i, j);
				return -EINVAL;
			}
		}
	}

	return 0;
}