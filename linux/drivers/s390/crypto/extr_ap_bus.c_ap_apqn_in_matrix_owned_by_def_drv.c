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
struct TYPE_2__ {unsigned long* apm; unsigned long* aqm; } ;

/* Variables and functions */
 int AP_DEVICES ; 
 int AP_DOMAINS ; 
 TYPE_1__ ap_perms ; 
 int /*<<< orphan*/  ap_perms_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit_inv (int,unsigned long*) ; 

int ap_apqn_in_matrix_owned_by_def_drv(unsigned long *apm,
				       unsigned long *aqm)
{
	int card, queue, rc = 0;

	mutex_lock(&ap_perms_mutex);

	for (card = 0; !rc && card < AP_DEVICES; card++)
		if (test_bit_inv(card, apm) &&
		    test_bit_inv(card, ap_perms.apm))
			for (queue = 0; !rc && queue < AP_DOMAINS; queue++)
				if (test_bit_inv(queue, aqm) &&
				    test_bit_inv(queue, ap_perms.aqm))
					rc = 1;

	mutex_unlock(&ap_perms_mutex);

	return rc;
}