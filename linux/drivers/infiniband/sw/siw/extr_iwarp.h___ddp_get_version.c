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
 int DDP_MASK_VERSION ; 
 int be16_to_cpu (int) ; 

__attribute__((used)) static inline u8 __ddp_get_version(struct iwarp_ctrl *ctrl)
{
	return be16_to_cpu(ctrl->ddp_rdmap_ctrl & DDP_MASK_VERSION) >> 8;
}