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
struct tb_switch {TYPE_1__* tb; scalar_t__ is_unplugged; } ;
typedef  enum tb_cfg_space { ____Placeholder_tb_cfg_space } tb_cfg_space ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int ENODEV ; 
 int tb_cfg_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tb_route (struct tb_switch*) ; 

__attribute__((used)) static inline int tb_sw_read(struct tb_switch *sw, void *buffer,
			     enum tb_cfg_space space, u32 offset, u32 length)
{
	if (sw->is_unplugged)
		return -ENODEV;
	return tb_cfg_read(sw->tb->ctl,
			   buffer,
			   tb_route(sw),
			   0,
			   space,
			   offset,
			   length);
}