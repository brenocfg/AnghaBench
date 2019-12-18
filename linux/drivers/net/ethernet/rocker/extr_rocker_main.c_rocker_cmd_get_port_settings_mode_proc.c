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
typedef  int /*<<< orphan*/  u8 ;
struct rocker_tlv {int dummy; } ;
struct rocker_port {int dummy; } ;
struct rocker_desc_info {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 size_t ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_MAX ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_SETTINGS_MAX ; 
 size_t ROCKER_TLV_CMD_PORT_SETTINGS_MODE ; 
 int /*<<< orphan*/  rocker_tlv_get_u8 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_desc (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_nested (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_tlv const*) ; 

__attribute__((used)) static int
rocker_cmd_get_port_settings_mode_proc(const struct rocker_port *rocker_port,
				       const struct rocker_desc_info *desc_info,
				       void *priv)
{
	u8 *p_mode = priv;
	const struct rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	const struct rocker_tlv *info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MAX + 1];
	const struct rocker_tlv *attr;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);
	if (!attrs[ROCKER_TLV_CMD_INFO])
		return -EIO;

	rocker_tlv_parse_nested(info_attrs, ROCKER_TLV_CMD_PORT_SETTINGS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);
	attr = info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MODE];
	if (!attr)
		return -EIO;

	*p_mode = rocker_tlv_get_u8(info_attrs[ROCKER_TLV_CMD_PORT_SETTINGS_MODE]);
	return 0;
}