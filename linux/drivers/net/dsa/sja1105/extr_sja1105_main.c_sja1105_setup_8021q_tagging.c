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
struct dsa_switch {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int dsa_port_setup_8021q_tagging (struct dsa_switch*,int,int) ; 

__attribute__((used)) static int sja1105_setup_8021q_tagging(struct dsa_switch *ds, bool enabled)
{
	int rc, i;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		rc = dsa_port_setup_8021q_tagging(ds, i, enabled);
		if (rc < 0) {
			dev_err(ds->dev, "Failed to setup VLAN tagging for port %d: %d\n",
				i, rc);
			return rc;
		}
	}
	dev_info(ds->dev, "%s switch tagging\n",
		 enabled ? "Enabled" : "Disabled");
	return 0;
}