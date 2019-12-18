#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ alpha_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*,scalar_t__) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ i915_modparams ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ kstrtou16 (char*,int,scalar_t__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static bool force_probe(u16 device_id, const char *devices)
{
	char *s, *p, *tok;
	bool ret;

	/* FIXME: transitional */
	if (i915_modparams.alpha_support) {
		DRM_INFO("i915.alpha_support is deprecated, use i915.force_probe=%04x instead\n",
			 device_id);
		return true;
	}

	if (!devices || !*devices)
		return false;

	/* match everything */
	if (strcmp(devices, "*") == 0)
		return true;

	s = kstrdup(devices, GFP_KERNEL);
	if (!s)
		return false;

	for (p = s, ret = false; (tok = strsep(&p, ",")) != NULL; ) {
		u16 val;

		if (kstrtou16(tok, 16, &val) == 0 && val == device_id) {
			ret = true;
			break;
		}
	}

	kfree(s);

	return ret;
}