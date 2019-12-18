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
struct rvu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcifunc; } ;
struct rsrc_detach {TYPE_1__ hdr; } ;
struct msg_rsp {int dummy; } ;

/* Variables and functions */
 int rvu_detach_rsrcs (struct rvu*,struct rsrc_detach*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rvu_mbox_handler_detach_resources(struct rvu *rvu,
					     struct rsrc_detach *detach,
					     struct msg_rsp *rsp)
{
	return rvu_detach_rsrcs(rvu, detach, detach->hdr.pcifunc);
}