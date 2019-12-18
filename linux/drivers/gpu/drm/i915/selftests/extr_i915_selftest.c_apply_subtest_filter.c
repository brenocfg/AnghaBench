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
struct TYPE_2__ {int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ i915_selftest ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static bool apply_subtest_filter(const char *caller, const char *name)
{
	char *filter, *sep, *tok;
	bool result = true;

	filter = kstrdup(i915_selftest.filter, GFP_KERNEL);
	for (sep = filter; (tok = strsep(&sep, ","));) {
		bool allow = true;
		char *sl;

		if (*tok == '!') {
			allow = false;
			tok++;
		}

		if (*tok == '\0')
			continue;

		sl = strchr(tok, '/');
		if (sl) {
			*sl++ = '\0';
			if (strcmp(tok, caller)) {
				if (allow)
					result = false;
				continue;
			}
			tok = sl;
		}

		if (strcmp(tok, name)) {
			if (allow)
				result = false;
			continue;
		}

		result = allow;
		break;
	}
	kfree(filter);

	return result;
}