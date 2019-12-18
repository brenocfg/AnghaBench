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
struct pxa_pinctrl_function {scalar_t__ name; } ;
struct pxa_pinctrl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static const struct pxa_pinctrl_function *
pxa2xx_find_function(struct pxa_pinctrl *pctl, const char *fname,
		     const struct pxa_pinctrl_function *functions)
{
	const struct pxa_pinctrl_function *func;

	for (func = functions; func->name; func++)
		if (!strcmp(fname, func->name))
			return func;

	return NULL;
}