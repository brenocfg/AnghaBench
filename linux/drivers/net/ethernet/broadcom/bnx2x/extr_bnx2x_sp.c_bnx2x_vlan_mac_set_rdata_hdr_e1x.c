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
typedef  scalar_t__ u8 ;
struct mac_configuration_hdr {int length; int /*<<< orphan*/  echo; int /*<<< orphan*/  client_id; scalar_t__ offset; } ;
struct bnx2x_raw_obj {int cid; } ;
struct bnx2x_vlan_mac_obj {struct bnx2x_raw_obj raw; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_SWCID_MASK ; 
 int BNX2X_SWCID_SHIFT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline void bnx2x_vlan_mac_set_rdata_hdr_e1x(struct bnx2x *bp,
	struct bnx2x_vlan_mac_obj *o, int type, int cam_offset,
	struct mac_configuration_hdr *hdr)
{
	struct bnx2x_raw_obj *r = &o->raw;

	hdr->length = 1;
	hdr->offset = (u8)cam_offset;
	hdr->client_id = cpu_to_le16(0xff);
	hdr->echo = cpu_to_le32((r->cid & BNX2X_SWCID_MASK) |
				(type << BNX2X_SWCID_SHIFT));
}