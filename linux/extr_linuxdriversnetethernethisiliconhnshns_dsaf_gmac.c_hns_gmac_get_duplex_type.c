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
typedef  enum hns_gmac_duplex_mdoe { ____Placeholder_hns_gmac_duplex_mdoe } hns_gmac_duplex_mdoe ;

/* Variables and functions */
 int /*<<< orphan*/  GMAC_DUPLEX_TYPE_B ; 
 int /*<<< orphan*/  GMAC_DUPLEX_TYPE_REG ; 
 scalar_t__ dsaf_get_dev_bit (struct mac_driver*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_gmac_get_duplex_type(void *mac_drv,
				     enum hns_gmac_duplex_mdoe *duplex_mode)
{
	struct mac_driver *drv = (struct mac_driver *)mac_drv;

	*duplex_mode = (enum hns_gmac_duplex_mdoe)dsaf_get_dev_bit(
		drv, GMAC_DUPLEX_TYPE_REG, GMAC_DUPLEX_TYPE_B);
}