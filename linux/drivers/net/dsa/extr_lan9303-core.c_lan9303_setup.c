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
struct lan9303 {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct lan9303* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LAN9303_SWE_GLB_INGRESS_CFG ; 
 int LAN9303_SWE_GLB_INGR_IGMP_PORT (int) ; 
 int LAN9303_SWE_GLB_INGR_IGMP_TRAP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dsa_is_cpu_port (struct dsa_switch*,int /*<<< orphan*/ ) ; 
 int lan9303_enable_processing_port (struct lan9303*,int /*<<< orphan*/ ) ; 
 int lan9303_separate_ports (struct lan9303*) ; 
 int lan9303_setup_tagging (struct lan9303*) ; 
 int lan9303_write_switch_reg_mask (struct lan9303*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lan9303_setup(struct dsa_switch *ds)
{
	struct lan9303 *chip = ds->priv;
	int ret;

	/* Make sure that port 0 is the cpu port */
	if (!dsa_is_cpu_port(ds, 0)) {
		dev_err(chip->dev, "port 0 is not the CPU port\n");
		return -EINVAL;
	}

	ret = lan9303_setup_tagging(chip);
	if (ret)
		dev_err(chip->dev, "failed to setup port tagging %d\n", ret);

	ret = lan9303_separate_ports(chip);
	if (ret)
		dev_err(chip->dev, "failed to separate ports %d\n", ret);

	ret = lan9303_enable_processing_port(chip, 0);
	if (ret)
		dev_err(chip->dev, "failed to re-enable switching %d\n", ret);

	/* Trap IGMP to port 0 */
	ret = lan9303_write_switch_reg_mask(chip, LAN9303_SWE_GLB_INGRESS_CFG,
					    LAN9303_SWE_GLB_INGR_IGMP_TRAP |
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(0),
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(1) |
					    LAN9303_SWE_GLB_INGR_IGMP_PORT(2));
	if (ret)
		dev_err(chip->dev, "failed to setup IGMP trap %d\n", ret);

	return 0;
}