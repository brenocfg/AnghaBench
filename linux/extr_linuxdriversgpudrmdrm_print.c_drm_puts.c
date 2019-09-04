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
struct drm_printer {int /*<<< orphan*/  (* puts ) (struct drm_printer*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,char const*) ; 
 int /*<<< orphan*/  stub1 (struct drm_printer*,char const*) ; 

void drm_puts(struct drm_printer *p, const char *str)
{
	if (p->puts)
		p->puts(p, str);
	else
		drm_printf(p, "%s", str);
}