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
struct qlcnic_bc_hdr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct qlcnic_bc_hdr* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qlcnic_sriov_alloc_bc_msg(struct qlcnic_bc_hdr **hdr,
					    u32 size)
{
	*hdr = kcalloc(size, sizeof(struct qlcnic_bc_hdr), GFP_ATOMIC);
	if (!*hdr)
		return -ENOMEM;

	return 0;
}