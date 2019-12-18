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
struct softing_platform_data {int manf; unsigned int prod; } ;

/* Variables and functions */
 struct softing_platform_data* softingcs_platform_data ; 

__attribute__((used)) static const struct softing_platform_data
*softingcs_find_platform_data(unsigned int manf, unsigned int prod)
{
	const struct softing_platform_data *lp;

	for (lp = softingcs_platform_data; lp->manf; ++lp) {
		if ((lp->manf == manf) && (lp->prod == prod))
			return lp;
	}
	return NULL;
}