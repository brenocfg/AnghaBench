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
struct va_format {int /*<<< orphan*/ * va; int /*<<< orphan*/  fmt; } ;
struct drm_printer {int /*<<< orphan*/  arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  i915_error_vprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __i915_printfn_error(struct drm_printer *p, struct va_format *vaf)
{
	i915_error_vprintf(p->arg, vaf->fmt, *vaf->va);
}