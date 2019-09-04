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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ u32 ;
struct phy_device {int dummy; } ;
struct dsa_switch {struct b53_device* priv; } ;
struct b53_mib_desc {int /*<<< orphan*/  name; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 unsigned int ETH_GSTRING_LEN ; 
 scalar_t__ ETH_SS_PHY_STATS ; 
 scalar_t__ ETH_SS_STATS ; 
 struct b53_mib_desc* b53_get_mib (struct b53_device*) ; 
 unsigned int b53_get_mib_size (struct b53_device*) ; 
 struct phy_device* b53_get_phy_device (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  phy_ethtool_get_strings (struct phy_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

void b53_get_strings(struct dsa_switch *ds, int port, u32 stringset,
		     uint8_t *data)
{
	struct b53_device *dev = ds->priv;
	const struct b53_mib_desc *mibs = b53_get_mib(dev);
	unsigned int mib_size = b53_get_mib_size(dev);
	struct phy_device *phydev;
	unsigned int i;

	if (stringset == ETH_SS_STATS) {
		for (i = 0; i < mib_size; i++)
			strlcpy(data + i * ETH_GSTRING_LEN,
				mibs[i].name, ETH_GSTRING_LEN);
	} else if (stringset == ETH_SS_PHY_STATS) {
		phydev = b53_get_phy_device(ds, port);
		if (!phydev)
			return;

		phy_ethtool_get_strings(phydev, data);
	}
}