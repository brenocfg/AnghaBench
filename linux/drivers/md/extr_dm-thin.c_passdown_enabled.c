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
struct TYPE_2__ {int discard_passdown; } ;
struct pool_c {TYPE_1__ adjusted_pf; } ;

/* Variables and functions */

__attribute__((used)) static bool passdown_enabled(struct pool_c *pt)
{
	return pt->adjusted_pf.discard_passdown;
}