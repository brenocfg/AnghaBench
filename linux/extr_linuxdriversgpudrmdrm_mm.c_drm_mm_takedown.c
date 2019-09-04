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
struct drm_mm {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*) ; 
 int /*<<< orphan*/  drm_mm_clean (struct drm_mm*) ; 
 int /*<<< orphan*/  show_leaks (struct drm_mm*) ; 

void drm_mm_takedown(struct drm_mm *mm)
{
	if (WARN(!drm_mm_clean(mm),
		 "Memory manager not clean during takedown.\n"))
		show_leaks(mm);
}