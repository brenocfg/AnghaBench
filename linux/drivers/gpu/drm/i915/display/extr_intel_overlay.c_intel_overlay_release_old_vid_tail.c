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
struct intel_overlay {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_overlay_release_old_vma (struct intel_overlay*) ; 

__attribute__((used)) static void
intel_overlay_release_old_vid_tail(struct intel_overlay *overlay)
{
	intel_overlay_release_old_vma(overlay);
}