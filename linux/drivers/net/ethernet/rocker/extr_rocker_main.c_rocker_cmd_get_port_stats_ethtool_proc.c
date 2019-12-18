#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct rocker_tlv {int dummy; } ;
struct rocker_port {scalar_t__ pport; } ;
struct rocker_desc_info {int dummy; } ;
struct TYPE_3__ {size_t type; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EIO ; 
 size_t ROCKER_TLV_CMD_INFO ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_MAX ; 
 int /*<<< orphan*/  ROCKER_TLV_CMD_PORT_STATS_MAX ; 
 size_t ROCKER_TLV_CMD_PORT_STATS_PPORT ; 
 TYPE_1__* rocker_port_stats ; 
 scalar_t__ rocker_tlv_get_u32 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_get_u64 (struct rocker_tlv const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_desc (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_desc_info const*) ; 
 int /*<<< orphan*/  rocker_tlv_parse_nested (struct rocker_tlv const**,int /*<<< orphan*/ ,struct rocker_tlv const*) ; 

__attribute__((used)) static int
rocker_cmd_get_port_stats_ethtool_proc(const struct rocker_port *rocker_port,
				       const struct rocker_desc_info *desc_info,
				       void *priv)
{
	const struct rocker_tlv *attrs[ROCKER_TLV_CMD_MAX + 1];
	const struct rocker_tlv *stats_attrs[ROCKER_TLV_CMD_PORT_STATS_MAX + 1];
	const struct rocker_tlv *pattr;
	u32 pport;
	u64 *data = priv;
	int i;

	rocker_tlv_parse_desc(attrs, ROCKER_TLV_CMD_MAX, desc_info);

	if (!attrs[ROCKER_TLV_CMD_INFO])
		return -EIO;

	rocker_tlv_parse_nested(stats_attrs, ROCKER_TLV_CMD_PORT_STATS_MAX,
				attrs[ROCKER_TLV_CMD_INFO]);

	if (!stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT])
		return -EIO;

	pport = rocker_tlv_get_u32(stats_attrs[ROCKER_TLV_CMD_PORT_STATS_PPORT]);
	if (pport != rocker_port->pport)
		return -EIO;

	for (i = 0; i < ARRAY_SIZE(rocker_port_stats); i++) {
		pattr = stats_attrs[rocker_port_stats[i].type];
		if (!pattr)
			continue;

		data[i] = rocker_tlv_get_u64(pattr);
	}

	return 0;
}