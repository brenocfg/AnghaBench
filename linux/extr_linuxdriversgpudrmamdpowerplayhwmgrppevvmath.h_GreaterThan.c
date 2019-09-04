#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ full; } ;
typedef  TYPE_1__ fInt ;

/* Variables and functions */

__attribute__((used)) static bool GreaterThan(fInt A, fInt B)
{
	if (A.full > B.full)
		return true;
	else
		return false;
}