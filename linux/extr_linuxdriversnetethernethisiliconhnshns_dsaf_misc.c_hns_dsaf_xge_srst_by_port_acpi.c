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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_OP_RESET_FUNC ; 
 int /*<<< orphan*/  HNS_XGE_RESET_FUNC ; 
 int /*<<< orphan*/  hns_dsaf_acpi_srst_by_port (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_dsaf_xge_srst_by_port_acpi(struct dsaf_device *dsaf_dev,
					   u32 port, bool dereset)
{
	hns_dsaf_acpi_srst_by_port(dsaf_dev, HNS_OP_RESET_FUNC,
				   HNS_XGE_RESET_FUNC, port, dereset);
}