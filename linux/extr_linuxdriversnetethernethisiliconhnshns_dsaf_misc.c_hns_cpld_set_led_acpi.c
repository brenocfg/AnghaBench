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
typedef  int /*<<< orphan*/  u16 ;
struct hns_mac_cb {int /*<<< orphan*/  mac_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_OP_LED_SET_FUNC ; 
 int /*<<< orphan*/  hns_dsaf_acpi_ledctrl_by_port (struct hns_mac_cb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void hns_cpld_set_led_acpi(struct hns_mac_cb *mac_cb, int link_status,
                            u16 speed, int data)
{
       if (!mac_cb) {
               pr_err("cpld_led_set mac_cb is null!\n");
               return;
       }

       hns_dsaf_acpi_ledctrl_by_port(mac_cb, HNS_OP_LED_SET_FUNC,
               link_status, mac_cb->mac_id, data);
}