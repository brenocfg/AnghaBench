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
struct TYPE_2__ {int /*<<< orphan*/  aqm; int /*<<< orphan*/  apm; } ;

/* Variables and functions */
 int AP_DEVICES ; 
 int AP_DOMAINS ; 
 int EINVAL ; 
 TYPE_1__ ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit_inv (int,int /*<<< orphan*/ ) ; 

int ap_owned_by_def_drv(int card, int queue)
{
	int rc = 0;

	if (card < 0 || card >= AP_DEVICES || queue < 0 || queue >= AP_DOMAINS)
		return -EINVAL;

	mutex_lock(&ap_perms_mutex);

	if (test_bit_inv(card, ap_perms.apm)
	    && test_bit_inv(queue, ap_perms.aqm))
		rc = 1;

	mutex_unlock(&ap_perms_mutex);

	return rc;
}