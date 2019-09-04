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
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_BM_EGRSS_PORT_TYPE ; 
 int /*<<< orphan*/  LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT0 ; 
 int /*<<< orphan*/  LAN9303_SWE_INGRESS_PORT_TYPE ; 
 int /*<<< orphan*/  LAN9303_SWE_INGRESS_PORT_TYPE_VLAN ; 
 int lan9303_write_switch_reg (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_setup_tagging(struct lan9303 *chip)
{
	int ret;
	u32 val;
	/* enable defining the destination port via special VLAN tagging
	 * for port 0
	 */
	ret = lan9303_write_switch_reg(chip, LAN9303_SWE_INGRESS_PORT_TYPE,
				       LAN9303_SWE_INGRESS_PORT_TYPE_VLAN);
	if (ret)
		return ret;

	/* tag incoming packets at port 1 and 2 on their way to port 0 to be
	 * able to discover their source port
	 */
	val = LAN9303_BM_EGRSS_PORT_TYPE_SPECIAL_TAG_PORT0;
	return lan9303_write_switch_reg(chip, LAN9303_BM_EGRSS_PORT_TYPE, val);
}