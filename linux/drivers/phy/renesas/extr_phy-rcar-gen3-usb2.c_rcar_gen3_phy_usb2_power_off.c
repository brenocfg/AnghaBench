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
struct rcar_gen3_phy {int powered; struct rcar_gen3_chan* ch; } ;
struct rcar_gen3_chan {int /*<<< orphan*/  lock; scalar_t__ vbus; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rcar_gen3_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  rcar_gen3_are_all_rphys_power_off (struct rcar_gen3_chan*) ; 
 int regulator_disable (scalar_t__) ; 

__attribute__((used)) static int rcar_gen3_phy_usb2_power_off(struct phy *p)
{
	struct rcar_gen3_phy *rphy = phy_get_drvdata(p);
	struct rcar_gen3_chan *channel = rphy->ch;
	int ret = 0;

	mutex_lock(&channel->lock);
	rphy->powered = false;

	if (!rcar_gen3_are_all_rphys_power_off(channel))
		goto out;

	if (channel->vbus)
		ret = regulator_disable(channel->vbus);

out:
	mutex_unlock(&channel->lock);

	return ret;
}