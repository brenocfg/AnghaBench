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
typedef  int u32 ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct hlist_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OPA_VNIC_MAC_TBL_SIZE ; 
 struct hlist_head* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_hash_init (struct hlist_head*) ; 

__attribute__((used)) static struct hlist_head *opa_vnic_alloc_mac_tbl(void)
{
	u32 size = sizeof(struct hlist_head) * OPA_VNIC_MAC_TBL_SIZE;
	struct hlist_head *mactbl;

	mactbl = kzalloc(size, GFP_KERNEL);
	if (!mactbl)
		return ERR_PTR(-ENOMEM);

	vnic_hash_init(mactbl);
	return mactbl;
}