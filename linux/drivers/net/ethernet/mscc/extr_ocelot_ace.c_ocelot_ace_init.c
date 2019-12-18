#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vcap_data {int dummy; } ;
struct ocelot {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {int /*<<< orphan*/  action_count; int /*<<< orphan*/  entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_POL_CIR_CFG ; 
 int /*<<< orphan*/  ANA_POL_CIR_STATE ; 
 int /*<<< orphan*/  ANA_POL_MODE_CFG ; 
 int /*<<< orphan*/  ANA_POL_PIR_CFG ; 
 int /*<<< orphan*/  ANA_POL_PIR_STATE ; 
 int /*<<< orphan*/  OCELOT_POLICER_DISCARD ; 
 int /*<<< orphan*/  S2_CORE_MV_CFG ; 
 int /*<<< orphan*/  VCAP_CMD_INITIALIZE ; 
 int VCAP_SEL_ACTION ; 
 int VCAP_SEL_COUNTER ; 
 int VCAP_SEL_ENTRY ; 
 int /*<<< orphan*/  acl_block ; 
 int /*<<< orphan*/  memset (struct vcap_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocelot_acl_block_create (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcap_action2cache (struct ocelot*,struct vcap_data*) ; 
 int /*<<< orphan*/  vcap_cmd (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcap_entry2cache (struct ocelot*,struct vcap_data*) ; 
 TYPE_1__ vcap_is2 ; 

int ocelot_ace_init(struct ocelot *ocelot)
{
	struct vcap_data data;

	memset(&data, 0, sizeof(data));
	vcap_entry2cache(ocelot, &data);
	ocelot_write(ocelot, vcap_is2.entry_count, S2_CORE_MV_CFG);
	vcap_cmd(ocelot, 0, VCAP_CMD_INITIALIZE, VCAP_SEL_ENTRY);

	vcap_action2cache(ocelot, &data);
	ocelot_write(ocelot, vcap_is2.action_count, S2_CORE_MV_CFG);
	vcap_cmd(ocelot, 0, VCAP_CMD_INITIALIZE,
		 VCAP_SEL_ACTION | VCAP_SEL_COUNTER);

	/* Create a policer that will drop the frames for the cpu.
	 * This policer will be used as action in the acl rules to drop
	 * frames.
	 */
	ocelot_write_gix(ocelot, 0x299, ANA_POL_MODE_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_write_gix(ocelot, 0x1, ANA_POL_PIR_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_write_gix(ocelot, 0x3fffff, ANA_POL_PIR_STATE,
			 OCELOT_POLICER_DISCARD);
	ocelot_write_gix(ocelot, 0x0, ANA_POL_CIR_CFG,
			 OCELOT_POLICER_DISCARD);
	ocelot_write_gix(ocelot, 0x3fffff, ANA_POL_CIR_STATE,
			 OCELOT_POLICER_DISCARD);

	acl_block = ocelot_acl_block_create(ocelot);

	return 0;
}