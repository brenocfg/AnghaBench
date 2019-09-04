#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pbt; int /*<<< orphan*/  blk0_len; int /*<<< orphan*/  version; int /*<<< orphan*/  len; } ;
struct ipl_parameter_block {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIAG308_IPL_TYPE_CCW ; 
 int /*<<< orphan*/  IPL_PARM_BLK0_CCW_LEN ; 
 int /*<<< orphan*/  IPL_PARM_BLK_CCW_LEN ; 
 int /*<<< orphan*/  IPL_PARM_BLOCK_VERSION ; 

__attribute__((used)) static void reipl_block_ccw_init(struct ipl_parameter_block *ipb)
{
	ipb->hdr.len = IPL_PARM_BLK_CCW_LEN;
	ipb->hdr.version = IPL_PARM_BLOCK_VERSION;
	ipb->hdr.blk0_len = IPL_PARM_BLK0_CCW_LEN;
	ipb->hdr.pbt = DIAG308_IPL_TYPE_CCW;
}