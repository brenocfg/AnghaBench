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
typedef  int /*<<< orphan*/  u32 ;
struct s5k6aa {TYPE_1__* gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s5k6aa_gpio_set_value(struct s5k6aa *priv, int id, u32 val)
{
	if (!gpio_is_valid(priv->gpio[id].gpio))
		return 0;
	gpio_set_value(priv->gpio[id].gpio, !!val);
	return 1;
}