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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct berlin_pinctrl_function {char** groups; int /*<<< orphan*/  ngroups; scalar_t__ name; } ;
struct berlin_pinctrl {int nfunctions; struct berlin_pinctrl_function* functions; TYPE_1__* desc; } ;
struct berlin_desc_group {int bit_width; char* name; struct berlin_desc_function* functions; } ;
struct berlin_desc_function {scalar_t__ name; } ;
struct TYPE_2__ {int ngroups; struct berlin_desc_group* groups; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  berlin_pinctrl_add_function (struct berlin_pinctrl*,scalar_t__) ; 
 char** devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct berlin_pinctrl_function* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct berlin_pinctrl_function*) ; 
 struct berlin_pinctrl_function* krealloc (struct berlin_pinctrl_function*,int,int /*<<< orphan*/ ) ; 
 struct berlin_pinctrl* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int berlin_pinctrl_build_state(struct platform_device *pdev)
{
	struct berlin_pinctrl *pctrl = platform_get_drvdata(pdev);
	const struct berlin_desc_group *desc_group;
	const struct berlin_desc_function *desc_function;
	int i, max_functions = 0;

	pctrl->nfunctions = 0;

	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		/* compute the maxiumum number of functions a group can have */
		max_functions += 1 << (desc_group->bit_width + 1);
	}

	/* we will reallocate later */
	pctrl->functions = kcalloc(max_functions,
				   sizeof(*pctrl->functions), GFP_KERNEL);
	if (!pctrl->functions)
		return -ENOMEM;

	/* register all functions */
	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->functions;

		while (desc_function->name) {
			berlin_pinctrl_add_function(pctrl, desc_function->name);
			desc_function++;
		}
	}

	pctrl->functions = krealloc(pctrl->functions,
				    pctrl->nfunctions * sizeof(*pctrl->functions),
				    GFP_KERNEL);

	/* map functions to theirs groups */
	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->functions;

		while (desc_function->name) {
			struct berlin_pinctrl_function
				*function = pctrl->functions;
			const char **groups;
			bool found = false;

			while (function->name) {
				if (!strcmp(desc_function->name, function->name)) {
					found = true;
					break;
				}
				function++;
			}

			if (!found) {
				kfree(pctrl->functions);
				return -EINVAL;
			}

			if (!function->groups) {
				function->groups =
					devm_kcalloc(&pdev->dev,
						     function->ngroups,
						     sizeof(char *),
						     GFP_KERNEL);

				if (!function->groups) {
					kfree(pctrl->functions);
					return -ENOMEM;
				}
			}

			groups = function->groups;
			while (*groups)
				groups++;

			*groups = desc_group->name;

			desc_function++;
		}
	}

	return 0;
}