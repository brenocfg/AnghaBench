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
struct iwarp_ctrl {int ddp_rdmap_ctrl; } ;

/* Variables and functions */
 int RDMAP_MASK_VERSION ; 
 int cpu_to_be16 (int) ; 

__attribute__((used)) static inline void __rdmap_set_version(struct iwarp_ctrl *ctrl, u8 version)
{
	ctrl->ddp_rdmap_ctrl = (ctrl->ddp_rdmap_ctrl & ~RDMAP_MASK_VERSION) |
			       (cpu_to_be16(version << 6) & RDMAP_MASK_VERSION);
}