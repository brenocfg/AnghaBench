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
struct pvr2_params {int val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pvr2_get_param_val(const struct pvr2_params *p, const char *s,
			      int size)
{
	int i;

	for (i = 0; i < size; i++) {
		if (!strncasecmp(p[i].name, s, strlen(s)))
			return p[i].val;
	}
	return -1;
}