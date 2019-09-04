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
struct intel_th_device {int /*<<< orphan*/  dev; } ;
struct gth_device {int* master; int /*<<< orphan*/  gth_lock; TYPE_1__* output; } ;
struct TYPE_2__ {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 unsigned int TH_CONFIGURABLE_MASTERS ; 
 struct gth_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
intel_th_gth_set_output(struct intel_th_device *thdev, unsigned int master)
{
	struct gth_device *gth = dev_get_drvdata(&thdev->dev);
	int port = 0; /* FIXME: make default output configurable */

	/*
	 * everything above TH_CONFIGURABLE_MASTERS is controlled by the
	 * same register
	 */
	if (master > TH_CONFIGURABLE_MASTERS)
		master = TH_CONFIGURABLE_MASTERS;

	spin_lock(&gth->gth_lock);
	if (gth->master[master] == -1) {
		set_bit(master, gth->output[port].master);
		gth->master[master] = port;
	}
	spin_unlock(&gth->gth_lock);

	return 0;
}