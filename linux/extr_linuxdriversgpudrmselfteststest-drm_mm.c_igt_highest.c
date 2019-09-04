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
 int /*<<< orphan*/  DRM_MM_INSERT_HIGH ; 
 int __igt_once (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igt_highest(void *ignored)
{
	return __igt_once(DRM_MM_INSERT_HIGH);
}