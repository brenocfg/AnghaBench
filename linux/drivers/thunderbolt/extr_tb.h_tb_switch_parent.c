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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct tb_switch {TYPE_1__ dev; } ;

/* Variables and functions */
 struct tb_switch* tb_to_switch (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct tb_switch *tb_switch_parent(struct tb_switch *sw)
{
	return tb_to_switch(sw->dev.parent);
}