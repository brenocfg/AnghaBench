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
struct intel_th_subdevice {scalar_t__ type; scalar_t__ otype; } ;
struct intel_th_device {int dummy; } ;
struct intel_th {int /*<<< orphan*/  num_thdevs; struct intel_th_device** thdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct intel_th_subdevice*) ; 
 int ENODEV ; 
 scalar_t__ GTH_NONE ; 
 scalar_t__ INTEL_TH_CAP (struct intel_th*,int /*<<< orphan*/ ) ; 
 scalar_t__ INTEL_TH_OUTPUT ; 
 scalar_t__ IS_ERR (struct intel_th_device*) ; 
 int PTR_ERR (struct intel_th_device*) ; 
 scalar_t__ host_mode ; 
 int /*<<< orphan*/  host_mode_only ; 
 struct intel_th_device* intel_th_subdevice_alloc (struct intel_th*,struct intel_th_subdevice const*) ; 
 struct intel_th_subdevice* intel_th_subdevices ; 

__attribute__((used)) static int intel_th_populate(struct intel_th *th)
{
	int src;

	/* create devices for each intel_th_subdevice */
	for (src = 0; src < ARRAY_SIZE(intel_th_subdevices); src++) {
		const struct intel_th_subdevice *subdev =
			&intel_th_subdevices[src];
		struct intel_th_device *thdev;

		/* only allow SOURCE and SWITCH devices in host mode */
		if ((INTEL_TH_CAP(th, host_mode_only) || host_mode) &&
		    subdev->type == INTEL_TH_OUTPUT)
			continue;

		/*
		 * don't enable port OUTPUTs in this path; SWITCH enables them
		 * via intel_th_output_enable()
		 */
		if (subdev->type == INTEL_TH_OUTPUT &&
		    subdev->otype != GTH_NONE)
			continue;

		thdev = intel_th_subdevice_alloc(th, subdev);
		/* note: caller should free subdevices from th::thdev[] */
		if (IS_ERR(thdev)) {
			/* ENODEV for individual subdevices is allowed */
			if (PTR_ERR(thdev) == -ENODEV)
				continue;

			return PTR_ERR(thdev);
		}

		th->thdev[th->num_thdevs++] = thdev;
	}

	return 0;
}