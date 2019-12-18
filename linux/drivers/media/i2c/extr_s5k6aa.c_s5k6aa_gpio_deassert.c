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
struct s5k6aa {TYPE_1__* gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int s5k6aa_gpio_set_value (struct s5k6aa*,int,int) ; 

__attribute__((used)) static int s5k6aa_gpio_deassert(struct s5k6aa *priv, int id)
{
	return s5k6aa_gpio_set_value(priv, id, !priv->gpio[id].level);
}