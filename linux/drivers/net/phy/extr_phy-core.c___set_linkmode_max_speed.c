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
typedef  scalar_t__ u32 ;
struct phy_setting {scalar_t__ speed; int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct phy_setting*) ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 struct phy_setting* settings ; 

__attribute__((used)) static int __set_linkmode_max_speed(u32 max_speed, unsigned long *addr)
{
	const struct phy_setting *p;
	int i;

	for (i = 0, p = settings; i < ARRAY_SIZE(settings); i++, p++) {
		if (p->speed > max_speed)
			linkmode_clear_bit(p->bit, addr);
		else
			break;
	}

	return 0;
}