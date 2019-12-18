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
struct dsa_switch {struct b53_device* priv; } ;
struct dsa_mall_mirror_tc_entry {int /*<<< orphan*/  to_local_port; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_EG_MIR_CTL ; 
 int /*<<< orphan*/  B53_IG_MIR_CTL ; 
 int /*<<< orphan*/  B53_MGMT_PAGE ; 
 int /*<<< orphan*/  B53_MIR_CAP_CTL ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  CAP_PORT_MASK ; 
 int /*<<< orphan*/  MIRROR_EN ; 
 int /*<<< orphan*/  b53_read16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int b53_mirror_add(struct dsa_switch *ds, int port,
		   struct dsa_mall_mirror_tc_entry *mirror, bool ingress)
{
	struct b53_device *dev = ds->priv;
	u16 reg, loc;

	if (ingress)
		loc = B53_IG_MIR_CTL;
	else
		loc = B53_EG_MIR_CTL;

	b53_read16(dev, B53_MGMT_PAGE, loc, &reg);
	reg |= BIT(port);
	b53_write16(dev, B53_MGMT_PAGE, loc, reg);

	b53_read16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, &reg);
	reg &= ~CAP_PORT_MASK;
	reg |= mirror->to_local_port;
	reg |= MIRROR_EN;
	b53_write16(dev, B53_MGMT_PAGE, B53_MIR_CAP_CTL, reg);

	return 0;
}