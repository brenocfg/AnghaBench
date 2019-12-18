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
struct TYPE_2__ {scalar_t__ extended_capabilities_len; int /*<<< orphan*/ * extended_capabilities_mask; int /*<<< orphan*/ * extended_capabilities; } ;
struct qtnf_wmac {TYPE_1__ macinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void qtnf_mac_ext_caps_free(struct qtnf_wmac *mac)
{
	if (mac->macinfo.extended_capabilities_len) {
		kfree(mac->macinfo.extended_capabilities);
		mac->macinfo.extended_capabilities = NULL;

		kfree(mac->macinfo.extended_capabilities_mask);
		mac->macinfo.extended_capabilities_mask = NULL;

		mac->macinfo.extended_capabilities_len = 0;
	}
}