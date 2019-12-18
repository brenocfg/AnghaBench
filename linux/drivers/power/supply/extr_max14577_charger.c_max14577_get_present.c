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
struct max14577_charger {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int max14577_get_present(struct max14577_charger *chg, int *val)
{
	*val = 1;

	return 0;
}