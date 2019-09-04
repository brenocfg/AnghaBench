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
 int /*<<< orphan*/  __is_raid10_offset (int) ; 
 int __raid10_near_copies (int) ; 

__attribute__((used)) static bool __is_raid10_near(int layout)
{
	return !__is_raid10_offset(layout) && __raid10_near_copies(layout) > 1;
}