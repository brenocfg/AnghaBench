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
struct mc13xxx {TYPE_1__* variant; } ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */

__attribute__((used)) static const char *mc13xxx_get_chipname(struct mc13xxx *mc13xxx)
{
	return mc13xxx->variant->name;
}