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
struct ScsiReqBlk {unsigned int sg_index; unsigned int sg_count; unsigned int total_xfer_length; struct SGentry* segment_x; } ;
struct SGentry {scalar_t__ length; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SG ; 
 scalar_t__ debug_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void sg_verify_length(struct ScsiReqBlk *srb)
{
	if (debug_enabled(DBG_SG)) {
		unsigned len = 0;
		unsigned idx = srb->sg_index;
		struct SGentry *psge = srb->segment_x + idx;
		for (; idx < srb->sg_count; psge++, idx++)
			len += psge->length;
		if (len != srb->total_xfer_length)
			dprintkdbg(DBG_SG,
			       "Inconsistent SRB S/G lengths (Tot=%i, Count=%i) !!\n",
			       srb->total_xfer_length, len);
	}			       
}