#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvmet_req {TYPE_3__* ns; TYPE_2__* cmd; } ;
struct TYPE_6__ {int blksize_shift; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {TYPE_1__ rw; } ;

/* Variables and functions */
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 nvmet_rw_len(struct nvmet_req *req)
{
	return ((u32)le16_to_cpu(req->cmd->rw.length) + 1) <<
			req->ns->blksize_shift;
}