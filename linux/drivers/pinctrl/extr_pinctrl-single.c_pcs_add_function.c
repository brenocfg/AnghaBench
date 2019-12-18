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
struct pcs_function {unsigned int nvals; struct pcs_func_vals* vals; } ;
struct pcs_func_vals {int dummy; } ;
struct pcs_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pctl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct pcs_function*) ; 
 struct pcs_function* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int pinmux_generic_add_function (int /*<<< orphan*/ ,char const*,char const**,unsigned int,struct pcs_function*) ; 

__attribute__((used)) static int pcs_add_function(struct pcs_device *pcs,
			    struct pcs_function **fcn,
			    const char *name,
			    struct pcs_func_vals *vals,
			    unsigned int nvals,
			    const char **pgnames,
			    unsigned int npgnames)
{
	struct pcs_function *function;
	int selector;

	function = devm_kzalloc(pcs->dev, sizeof(*function), GFP_KERNEL);
	if (!function)
		return -ENOMEM;

	function->vals = vals;
	function->nvals = nvals;

	selector = pinmux_generic_add_function(pcs->pctl, name,
					       pgnames, npgnames,
					       function);
	if (selector < 0) {
		devm_kfree(pcs->dev, function);
		*fcn = NULL;
	} else {
		*fcn = function;
	}

	return selector;
}