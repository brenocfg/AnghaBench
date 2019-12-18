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
typedef  int /*<<< orphan*/  u32 ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_SET_ST ; 
 int /*<<< orphan*/  DME_PEER ; 
 int ufshcd_dme_set_attr (struct ufs_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ufshcd_dme_peer_st_set(struct ufs_hba *hba, u32 attr_sel,
					 u32 mib_val)
{
	return ufshcd_dme_set_attr(hba, attr_sel, ATTR_SET_ST,
				   mib_val, DME_PEER);
}