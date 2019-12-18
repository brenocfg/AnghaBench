#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {TYPE_2__* request; } ;
struct TYPE_4__ {TYPE_1__* rq_disk; } ;
struct TYPE_3__ {char const* disk_name; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *scmd_name(const struct scsi_cmnd *scmd)
{
	return scmd->request->rq_disk ?
		scmd->request->rq_disk->disk_name : NULL;
}