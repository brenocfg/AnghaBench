#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  function; } ;
struct TYPE_4__ {TYPE_1__ mux; } ;
struct pinctrl_map {int /*<<< orphan*/  name; TYPE_2__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int pinmux_validate_map(const struct pinctrl_map *map, int i)
{
	if (!map->data.mux.function) {
		pr_err("failed to register map %s (%d): no function given\n",
		       map->name, i);
		return -EINVAL;
	}

	return 0;
}