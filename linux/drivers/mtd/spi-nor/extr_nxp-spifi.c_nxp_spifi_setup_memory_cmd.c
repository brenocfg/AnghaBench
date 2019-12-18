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
struct TYPE_2__ {int read_proto; int addr_width; int read_dummy; int /*<<< orphan*/  read_opcode; } ;
struct nxp_spifi {int mcmd; TYPE_1__ nor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNOR_PROTO_1_1_1 130 
#define  SNOR_PROTO_1_1_2 129 
#define  SNOR_PROTO_1_1_4 128 
 int SPIFI_CMD_FIELDFORM_ALL_SERIAL ; 
 int SPIFI_CMD_FIELDFORM_QUAD_DUAL_DATA ; 
 int SPIFI_CMD_FRAMEFORM (int) ; 
 int SPIFI_CMD_INTLEN (int) ; 
 int SPIFI_CMD_OPCODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int nxp_spifi_setup_memory_cmd(struct nxp_spifi *spifi)
{
	switch (spifi->nor.read_proto) {
	case SNOR_PROTO_1_1_1:
		spifi->mcmd = SPIFI_CMD_FIELDFORM_ALL_SERIAL;
		break;
	case SNOR_PROTO_1_1_2:
	case SNOR_PROTO_1_1_4:
		spifi->mcmd = SPIFI_CMD_FIELDFORM_QUAD_DUAL_DATA;
		break;
	default:
		dev_err(spifi->dev, "unsupported SPI read mode\n");
		return -EINVAL;
	}

	/* Memory mode supports address length between 1 and 4 */
	if (spifi->nor.addr_width < 1 || spifi->nor.addr_width > 4)
		return -EINVAL;

	spifi->mcmd |= SPIFI_CMD_OPCODE(spifi->nor.read_opcode) |
		       SPIFI_CMD_INTLEN(spifi->nor.read_dummy / 8) |
		       SPIFI_CMD_FRAMEFORM(spifi->nor.addr_width + 1);

	return 0;
}