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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct b53_device {int dummy; } ;
struct b53_arl_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_ARLIO_PAGE ; 
 int /*<<< orphan*/  B53_ARL_SRCH_RSTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B53_ARL_SRCH_RSTL_MACVID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_arl_to_entry (struct b53_arl_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_read32 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  b53_read64 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b53_arl_search_rd(struct b53_device *dev, u8 idx,
			      struct b53_arl_entry *ent)
{
	u64 mac_vid;
	u32 fwd_entry;

	b53_read64(dev, B53_ARLIO_PAGE,
		   B53_ARL_SRCH_RSTL_MACVID(idx), &mac_vid);
	b53_read32(dev, B53_ARLIO_PAGE,
		   B53_ARL_SRCH_RSTL(idx), &fwd_entry);
	b53_arl_to_entry(ent, mac_vid, fwd_entry);
}