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

/* Variables and functions */
 scalar_t__ machine_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpc8544_ds ; 
 int /*<<< orphan*/  mpc8572_ds ; 
 int /*<<< orphan*/  mpc86xx_hpcn ; 
 int /*<<< orphan*/  p2020_ds ; 

__attribute__((used)) static inline bool is_quirk_valid(void)
{
	return (machine_is(mpc86xx_hpcn) ||
		machine_is(mpc8544_ds) ||
		machine_is(p2020_ds) ||
		machine_is(mpc8572_ds));
}