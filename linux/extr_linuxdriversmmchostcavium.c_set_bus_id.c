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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  clear_bus_id (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_bus_id(u64 *reg, int bus_id)
{
	clear_bus_id(reg);
	*reg |= FIELD_PREP(GENMASK(61, 60), bus_id);
}