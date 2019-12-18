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
struct s5k4ecgx {TYPE_1__* gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k4ecgx_free_gpios(struct s5k4ecgx *priv)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(priv->gpio); i++) {
		if (!gpio_is_valid(priv->gpio[i].gpio))
			continue;
		gpio_free(priv->gpio[i].gpio);
		priv->gpio[i].gpio = -EINVAL;
	}
}