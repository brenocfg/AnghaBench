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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int cik_cp_compute_resume (struct radeon_device*) ; 
 int cik_cp_gfx_resume (struct radeon_device*) ; 
 int cik_cp_load_microcode (struct radeon_device*) ; 
 int /*<<< orphan*/  cik_enable_gui_idle_interrupt (struct radeon_device*,int) ; 

__attribute__((used)) static int cik_cp_resume(struct radeon_device *rdev)
{
	int r;

	cik_enable_gui_idle_interrupt(rdev, false);

	r = cik_cp_load_microcode(rdev);
	if (r)
		return r;

	r = cik_cp_gfx_resume(rdev);
	if (r)
		return r;
	r = cik_cp_compute_resume(rdev);
	if (r)
		return r;

	cik_enable_gui_idle_interrupt(rdev, true);

	return 0;
}