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
struct ap_queue_status {scalar_t__ response_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  aqm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DBF (int /*<<< orphan*/ ,char*,int) ; 
 int AP_DEVICES ; 
 int AP_DOMAINS ; 
 int /*<<< orphan*/  AP_MKQID (int,int) ; 
 scalar_t__ AP_RESPONSE_NORMAL ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  ap_apft_available () ; 
 int ap_domain_index ; 
 int /*<<< orphan*/  ap_domain_lock ; 
 TYPE_1__ ap_perms ; 
 int /*<<< orphan*/  ap_test_config_card_id (int) ; 
 int /*<<< orphan*/  ap_test_config_usage_domain (int) ; 
 struct ap_queue_status ap_test_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit_inv (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ap_select_domain(void)
{
	int count, max_count, best_domain;
	struct ap_queue_status status;
	int i, j;

	/*
	 * We want to use a single domain. Either the one specified with
	 * the "domain=" parameter or the domain with the maximum number
	 * of devices.
	 */
	spin_lock_bh(&ap_domain_lock);
	if (ap_domain_index >= 0) {
		/* Domain has already been selected. */
		spin_unlock_bh(&ap_domain_lock);
		return;
	}
	best_domain = -1;
	max_count = 0;
	for (i = 0; i < AP_DOMAINS; i++) {
		if (!ap_test_config_usage_domain(i) ||
		    !test_bit_inv(i, ap_perms.aqm))
			continue;
		count = 0;
		for (j = 0; j < AP_DEVICES; j++) {
			if (!ap_test_config_card_id(j))
				continue;
			status = ap_test_queue(AP_MKQID(j, i),
					       ap_apft_available(),
					       NULL);
			if (status.response_code != AP_RESPONSE_NORMAL)
				continue;
			count++;
		}
		if (count > max_count) {
			max_count = count;
			best_domain = i;
		}
	}
	if (best_domain >= 0) {
		ap_domain_index = best_domain;
		AP_DBF(DBF_DEBUG, "new ap_domain_index=%d\n", ap_domain_index);
	}
	spin_unlock_bh(&ap_domain_lock);
}