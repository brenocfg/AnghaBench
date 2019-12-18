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
struct mac_driver {int dummy; } ;
typedef  enum hns_port_mode { ____Placeholder_hns_port_mode } hns_port_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_PORT_MODE_M ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_REG ; 
 int /*<<< orphan*/  GMAC_PORT_MODE_S ; 
 scalar_t__ dsaf_get_dev_field (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_get_port_mode(void *mac_drv, enum hns_port_mode *port_mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*port_mode = (enum hns_port_mode)dsaf_get_dev_field(
		drv, GMAC_PORT_MODE_REG, GMAC_PORT_MODE_M, GMAC_PORT_MODE_S);
}