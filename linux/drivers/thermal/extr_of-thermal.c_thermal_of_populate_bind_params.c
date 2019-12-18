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
typedef  int /*<<< orphan*/  u32 ;
struct thermal_trip {struct device_node* np; } ;
struct of_phandle_args {int args_count; int /*<<< orphan*/ * args; struct device_node* np; } ;
struct device_node {int dummy; } ;
struct __thermal_cooling_bind_param {struct device_node* cooling_device; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct __thermal_bind_params {int trip_id; int count; struct __thermal_cooling_bind_param* tcbp; int /*<<< orphan*/  usage; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THERMAL_WEIGHT_DEFAULT ; 
 struct __thermal_cooling_bind_param* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct __thermal_cooling_bind_param*) ; 
 int of_count_phandle_with_args (struct device_node*,char*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,struct of_phandle_args*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int thermal_of_populate_bind_params(struct device_node *np,
					   struct __thermal_bind_params *__tbp,
					   struct thermal_trip *trips,
					   int ntrips)
{
	struct of_phandle_args cooling_spec;
	struct __thermal_cooling_bind_param *__tcbp;
	struct device_node *trip;
	int ret, i, count;
	u32 prop;

	/* Default weight. Usage is optional */
	__tbp->usage = THERMAL_WEIGHT_DEFAULT;
	ret = of_property_read_u32(np, "contribution", &prop);
	if (ret == 0)
		__tbp->usage = prop;

	trip = of_parse_phandle(np, "trip", 0);
	if (!trip) {
		pr_err("missing trip property\n");
		return -ENODEV;
	}

	/* match using device_node */
	for (i = 0; i < ntrips; i++)
		if (trip == trips[i].np) {
			__tbp->trip_id = i;
			break;
		}

	if (i == ntrips) {
		ret = -ENODEV;
		goto end;
	}

	count = of_count_phandle_with_args(np, "cooling-device",
					   "#cooling-cells");
	if (!count) {
		pr_err("Add a cooling_device property with at least one device\n");
		goto end;
	}

	__tcbp = kcalloc(count, sizeof(*__tcbp), GFP_KERNEL);
	if (!__tcbp)
		goto end;

	for (i = 0; i < count; i++) {
		ret = of_parse_phandle_with_args(np, "cooling-device",
				"#cooling-cells", i, &cooling_spec);
		if (ret < 0) {
			pr_err("Invalid cooling-device entry\n");
			goto free_tcbp;
		}

		__tcbp[i].cooling_device = cooling_spec.np;

		if (cooling_spec.args_count >= 2) { /* at least min and max */
			__tcbp[i].min = cooling_spec.args[0];
			__tcbp[i].max = cooling_spec.args[1];
		} else {
			pr_err("wrong reference to cooling device, missing limits\n");
		}
	}

	__tbp->tcbp = __tcbp;
	__tbp->count = count;

	goto end;

free_tcbp:
	for (i = i - 1; i >= 0; i--)
		of_node_put(__tcbp[i].cooling_device);
	kfree(__tcbp);
end:
	of_node_put(trip);

	return ret;
}