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
struct arglist {int dummy; } ;

/* Variables and functions */
 scalar_t__ kstrtoul (char*,int /*<<< orphan*/ ,unsigned long*) ; 
 char* uml_vector_fetch_arg (struct arglist*,char*) ; 

__attribute__((used)) static bool get_ulong_param(
	struct arglist *def, char *param, unsigned long *result)
{
	char *arg = uml_vector_fetch_arg(def, param);

	if (arg != NULL) {
		if (kstrtoul(arg, 0, result) == 0)
			return true;
		return true;
	}
	return false;
}