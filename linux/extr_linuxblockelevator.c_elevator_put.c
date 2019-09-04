#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elevator_type {int /*<<< orphan*/  elevator_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void elevator_put(struct elevator_type *e)
{
	module_put(e->elevator_owner);
}