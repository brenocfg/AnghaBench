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
struct ScsiReqBlk {scalar_t__ total_xfer_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  sg_update_list (struct ScsiReqBlk*,scalar_t__) ; 

__attribute__((used)) static void sg_subtract_one(struct ScsiReqBlk *srb)
{
	sg_update_list(srb, srb->total_xfer_length - 1);
}