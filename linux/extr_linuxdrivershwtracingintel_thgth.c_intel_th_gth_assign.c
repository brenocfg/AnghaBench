#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int port; int active; } ;
struct intel_th_device {scalar_t__ type; int id; TYPE_2__ output; scalar_t__ host_mode; int /*<<< orphan*/  dev; } ;
struct gth_device {int /*<<< orphan*/  gth_lock; TYPE_1__* output; } ;
struct TYPE_3__ {scalar_t__ port_type; TYPE_2__* output; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ INTEL_TH_OUTPUT ; 
 int TH_POSSIBLE_OUTPUTS ; 
 struct gth_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int intel_th_gth_assign(struct intel_th_device *thdev,
			       struct intel_th_device *othdev)
{
	struct gth_device *gth = dev_get_drvdata(&thdev->dev);
	int i, id;

	if (thdev->host_mode)
		return -EBUSY;

	if (othdev->type != INTEL_TH_OUTPUT)
		return -EINVAL;

	for (i = 0, id = 0; i < TH_POSSIBLE_OUTPUTS; i++) {
		if (gth->output[i].port_type != othdev->output.type)
			continue;

		if (othdev->id == -1 || othdev->id == id)
			goto found;

		id++;
	}

	return -ENOENT;

found:
	spin_lock(&gth->gth_lock);
	othdev->output.port = i;
	othdev->output.active = false;
	gth->output[i].output = &othdev->output;
	spin_unlock(&gth->gth_lock);

	return 0;
}