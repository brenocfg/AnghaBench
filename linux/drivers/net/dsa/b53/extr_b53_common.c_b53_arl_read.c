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
typedef  unsigned int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {unsigned int num_arl_entries; } ;
struct b53_arl_entry {int dummy; } ;

/* Variables and functions */
 int ARLTBL_MAC_MASK ; 
 int ARLTBL_VALID ; 
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARLTBL_DATA_ENTRY (unsigned int) ; 
 int /*<<< orphan*/  B53_ARLTBL_MAC_VID_ENTRY (unsigned int) ; 
 int ENOENT ; 
 int b53_arl_op_wait (struct b53_device*) ; 
 int /*<<< orphan*/  b53_arl_to_entry (struct b53_arl_entry*,int,int) ; 
 int /*<<< orphan*/  b53_read32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_read64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int b53_arl_read(struct b53_device *dev, u64 mac,
			u16 vid, struct b53_arl_entry *ent, u8 *idx,
			bool is_valid)
{
	unsigned int i;
	int ret;

	ret = b53_arl_op_wait(dev);
	if (ret)
		return ret;

	/* Read the bins */
	for (i = 0; i < dev->num_arl_entries; i++) {
		u64 mac_vid;
		u32 fwd_entry;

		b53_read64(dev, B53_ARLIO_PAGE,
			   B53_ARLTBL_MAC_VID_ENTRY(i), &mac_vid);
		b53_read32(dev, B53_ARLIO_PAGE,
			   B53_ARLTBL_DATA_ENTRY(i), &fwd_entry);
		b53_arl_to_entry(ent, mac_vid, fwd_entry);

		if (!(fwd_entry & ARLTBL_VALID))
			continue;
		if ((mac_vid & ARLTBL_MAC_MASK) != mac)
			continue;
		*idx = i;
	}

	return -ENOENT;
}