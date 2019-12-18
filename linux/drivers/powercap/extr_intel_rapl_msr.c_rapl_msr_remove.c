#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  control_type; int /*<<< orphan*/  pcap_rapl_online; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powercap_unregister_control_type (int /*<<< orphan*/ ) ; 
 TYPE_1__ rapl_msr_priv ; 
 int /*<<< orphan*/  rapl_remove_platform_domain (TYPE_1__*) ; 

__attribute__((used)) static int rapl_msr_remove(struct platform_device *pdev)
{
	cpuhp_remove_state(rapl_msr_priv.pcap_rapl_online);
	rapl_remove_platform_domain(&rapl_msr_priv);
	powercap_unregister_control_type(rapl_msr_priv.control_type);
	return 0;
}