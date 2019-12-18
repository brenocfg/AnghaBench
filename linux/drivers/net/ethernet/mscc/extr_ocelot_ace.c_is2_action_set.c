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
struct vcap_data {int dummy; } ;
typedef  enum ocelot_ace_action { ____Placeholder_ocelot_ace_action } ocelot_ace_action ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_COPY_ENA ; 
 int /*<<< orphan*/  CPU_QU_NUM ; 
 int /*<<< orphan*/  MASK_MODE ; 
#define  OCELOT_ACL_ACTION_DROP 129 
#define  OCELOT_ACL_ACTION_TRAP 128 
 int OCELOT_POLICER_DISCARD ; 
 int /*<<< orphan*/  POLICE_ENA ; 
 int /*<<< orphan*/  POLICE_IDX ; 
 int /*<<< orphan*/  PORT_MASK ; 
 int /*<<< orphan*/  VCAP_ACT_SET (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void is2_action_set(struct vcap_data *data,
			   enum ocelot_ace_action action)
{
	switch (action) {
	case OCELOT_ACL_ACTION_DROP:
		VCAP_ACT_SET(PORT_MASK, 0x0);
		VCAP_ACT_SET(MASK_MODE, 0x1);
		VCAP_ACT_SET(POLICE_ENA, 0x1);
		VCAP_ACT_SET(POLICE_IDX, OCELOT_POLICER_DISCARD);
		VCAP_ACT_SET(CPU_QU_NUM, 0x0);
		VCAP_ACT_SET(CPU_COPY_ENA, 0x0);
		break;
	case OCELOT_ACL_ACTION_TRAP:
		VCAP_ACT_SET(PORT_MASK, 0x0);
		VCAP_ACT_SET(MASK_MODE, 0x1);
		VCAP_ACT_SET(POLICE_ENA, 0x0);
		VCAP_ACT_SET(POLICE_IDX, 0x0);
		VCAP_ACT_SET(CPU_QU_NUM, 0x0);
		VCAP_ACT_SET(CPU_COPY_ENA, 0x1);
		break;
	}
}