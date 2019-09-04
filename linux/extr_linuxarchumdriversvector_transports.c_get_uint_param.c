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
 scalar_t__ kstrtoint (char*,int /*<<< orphan*/ ,unsigned int*) ; 
 char* uml_vector_fetch_arg (struct arglist*,char*) ; 

__attribute__((used)) static bool get_uint_param(
	struct arglist *def, char *param, unsigned int *result)
{
	char *arg = uml_vector_fetch_arg(def, param);

	if (arg != NULL) {
		if (kstrtoint(arg, 0, result) == 0)
			return true;
	}
	return false;
}