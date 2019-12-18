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
struct pcmcia_device {TYPE_2__* priv; } ;
struct TYPE_4__ {TYPE_1__* host; scalar_t__ stop; } ;
typedef  TYPE_2__ scsi_info_t ;
typedef  int /*<<< orphan*/  nsp_hw_data ;
struct TYPE_3__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  NSP_DEBUG_INIT ; 
 int /*<<< orphan*/  nsp_bus_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsp_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsp_msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nsphw_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nsp_cs_resume(struct pcmcia_device *link)
{
	scsi_info_t *info = link->priv;
	nsp_hw_data *data;

	nsp_dbg(NSP_DEBUG_INIT, "event: resume");

	info->stop = 0;

	if (info->host != NULL) {
		nsp_msg(KERN_INFO, "reset host and bus");

		data = (nsp_hw_data *)info->host->hostdata;

		nsphw_init   (data);
		nsp_bus_reset(data);
	}

	return 0;
}