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
struct regmap_range_node {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  (* format_write ) (struct regmap*,unsigned int,unsigned int) ;} ;
struct regmap {TYPE_2__ format; int /*<<< orphan*/  work_buf; int /*<<< orphan*/  bus_context; TYPE_1__* bus; } ;
struct TYPE_3__ {int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct regmap_range_node* _regmap_range_lookup (struct regmap*,unsigned int) ; 
 int _regmap_select_page (struct regmap*,unsigned int*,struct regmap_range_node*,int) ; 
 int /*<<< orphan*/  stub1 (struct regmap*,unsigned int,unsigned int) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_regmap_hw_write_done (struct regmap*,unsigned int,int) ; 
 int /*<<< orphan*/  trace_regmap_hw_write_start (struct regmap*,unsigned int,int) ; 

__attribute__((used)) static int _regmap_bus_formatted_write(void *context, unsigned int reg,
				       unsigned int val)
{
	int ret;
	struct regmap_range_node *range;
	struct regmap *map = context;

	WARN_ON(!map->bus || !map->format.format_write);

	range = _regmap_range_lookup(map, reg);
	if (range) {
		ret = _regmap_select_page(map, &reg, range, 1);
		if (ret != 0)
			return ret;
	}

	map->format.format_write(map, reg, val);

	trace_regmap_hw_write_start(map, reg, 1);

	ret = map->bus->write(map->bus_context, map->work_buf,
			      map->format.buf_size);

	trace_regmap_hw_write_done(map, reg, 1);

	return ret;
}