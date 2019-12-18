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
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_puts (struct drm_printer*,char const*) ; 

__attribute__((used)) static void print_name(struct drm_printer *p, const char *fmt, const char *name)
{
	drm_puts(p, fmt);
	drm_puts(p, name);
	drm_puts(p, "\n");
}