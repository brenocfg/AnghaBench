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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {TYPE_1__* ns; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno_to_nvme_status (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_fsync (int /*<<< orphan*/ ,int) ; 

u16 nvmet_file_flush(struct nvmet_req *req)
{
	return errno_to_nvme_status(req, vfs_fsync(req->ns->file, 1));
}