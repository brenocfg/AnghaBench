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
struct phy_device {int dummy; } ;
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_eee_enable_set (struct dsa_switch*,int,int) ; 
 int phy_init_eee (struct phy_device*,int /*<<< orphan*/ ) ; 

int b53_eee_init(struct dsa_switch *ds, int port, struct phy_device *phy)
{
	int ret;

	ret = phy_init_eee(phy, 0);
	if (ret)
		return 0;

	b53_eee_enable_set(ds, port, true);

	return 1;
}