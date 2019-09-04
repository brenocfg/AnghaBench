#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int active_area; int nr_areas; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */

__attribute__((used)) static inline void proceed_active_area(debug_info_t *id)
{
	id->active_area++;
	id->active_area = id->active_area % id->nr_areas;
}