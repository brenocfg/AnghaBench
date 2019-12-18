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
struct rocker_tlv {int dummy; } ;
struct rocker_port {int /*<<< orphan*/  pport; } ;
struct rocker_desc_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_PPORT ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_SPEED ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS ; 
 int /*<<< orphan*/  rocker_tlv_nest_end (struct rocker_desc_info*,struct rocker_tlv*) ; 
 struct rocker_tlv* rocker_tlv_nest_start (struct rocker_desc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u16 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u32 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rocker_tlv_put_u8 (struct rocker_desc_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rocker_cmd_set_port_settings_ethtool_prep(const struct rocker_port *rocker_port,
					  struct rocker_desc_info *desc_info,
					  void *priv)
{
	struct ethtool_link_ksettings *ecmd = priv;
	struct rocker_tlv *cmd_info;

	if (rocker_tlv_put_u16(desc_info, ROCKER_TLV_CMD_TYPE,
			       ROCKER_TLV_CMD_TYPE_SET_PORT_SETTINGS))
		return -EMSGSIZE;
	cmd_info = rocker_tlv_nest_start(desc_info, ROCKER_TLV_CMD_INFO);
	if (!cmd_info)
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_PPORT,
			       rocker_port->pport))
		return -EMSGSIZE;
	if (rocker_tlv_put_u32(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_SPEED,
			       ecmd->base.speed))
		return -EMSGSIZE;
	if (rocker_tlv_put_u8(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_DUPLEX,
			      ecmd->base.duplex))
		return -EMSGSIZE;
	if (rocker_tlv_put_u8(desc_info, ROCKER_TLV_CMD_PORT_SETTINGS_AUTONEG,
			      ecmd->base.autoneg))
		return -EMSGSIZE;
	rocker_tlv_nest_end(desc_info, cmd_info);
	return 0;
}