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
struct intel_timeline {int dummy; } ;

/* Variables and functions */
 struct intel_timeline* intel_timeline_get (struct intel_timeline*) ; 
 int /*<<< orphan*/  intel_timeline_put (struct intel_timeline*) ; 

__attribute__((used)) static void __set_timeline(struct intel_timeline **dst,
			   struct intel_timeline *src)
{
	struct intel_timeline *old = *dst;

	*dst = src ? intel_timeline_get(src) : NULL;

	if (old)
		intel_timeline_put(old);
}