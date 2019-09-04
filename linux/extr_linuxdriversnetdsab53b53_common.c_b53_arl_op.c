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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {int dummy; } ;
struct b53_arl_entry {int port; int is_valid; int is_static; int /*<<< orphan*/  mac; int /*<<< orphan*/  vid; } ;
typedef  int /*<<< orphan*/  ent ;

/* Variables and functions */
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARLTBL_DATA_ENTRY (int) ; 
 int /*<<< orphan*/  B53_ARLTBL_MAC_VID_ENTRY (int) ; 
 int /*<<< orphan*/  B53_MAC_ADDR_IDX ; 
 int /*<<< orphan*/  B53_VLAN_ID_IDX ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  b53_arl_from_entry (int /*<<< orphan*/ *,scalar_t__*,struct b53_arl_entry*) ; 
 int b53_arl_read (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct b53_arl_entry*,int*,int) ; 
 int b53_arl_rw_op (struct b53_device*,int) ; 
 int /*<<< orphan*/  b53_write16 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  b53_write48 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_write64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_to_u64 (unsigned char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct b53_arl_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int b53_arl_op(struct b53_device *dev, int op, int port,
		      const unsigned char *addr, u16 vid, bool is_valid)
{
	struct b53_arl_entry ent;
	u32 fwd_entry;
	u64 mac, mac_vid = 0;
	u8 idx = 0;
	int ret;

	/* Convert the array into a 64-bit MAC */
	mac = ether_addr_to_u64(addr);

	/* Perform a read for the given MAC and VID */
	b53_write48(dev, B53_ARLIO_PAGE, B53_MAC_ADDR_IDX, mac);
	b53_write16(dev, B53_ARLIO_PAGE, B53_VLAN_ID_IDX, vid);

	/* Issue a read operation for this MAC */
	ret = b53_arl_rw_op(dev, 1);
	if (ret)
		return ret;

	ret = b53_arl_read(dev, mac, vid, &ent, &idx, is_valid);
	/* If this is a read, just finish now */
	if (op)
		return ret;

	/* We could not find a matching MAC, so reset to a new entry */
	if (ret) {
		fwd_entry = 0;
		idx = 1;
	}

	memset(&ent, 0, sizeof(ent));
	ent.port = port;
	ent.is_valid = is_valid;
	ent.vid = vid;
	ent.is_static = true;
	memcpy(ent.mac, addr, ETH_ALEN);
	b53_arl_from_entry(&mac_vid, &fwd_entry, &ent);

	b53_write64(dev, B53_ARLIO_PAGE,
		    B53_ARLTBL_MAC_VID_ENTRY(idx), mac_vid);
	b53_write32(dev, B53_ARLIO_PAGE,
		    B53_ARLTBL_DATA_ENTRY(idx), fwd_entry);

	return b53_arl_rw_op(dev, 0);
}