#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {size_t mode; int /*<<< orphan*/  recon_tmo; TYPE_2__* dev; } ;
typedef  TYPE_3__ ppa_struct ;
struct TYPE_6__ {TYPE_1__* port; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PPA_MODE_STRING ; 
 int /*<<< orphan*/  PPA_VERSION ; 
 TYPE_3__* ppa_dev (struct Scsi_Host*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ppa_show_info(struct seq_file *m, struct Scsi_Host *host)
{
	ppa_struct *dev = ppa_dev(host);

	seq_printf(m, "Version : %s\n", PPA_VERSION);
	seq_printf(m, "Parport : %s\n", dev->dev->port->name);
	seq_printf(m, "Mode    : %s\n", PPA_MODE_STRING[dev->mode]);
#if PPA_DEBUG > 0
	seq_printf(m, "recon_tmo : %lu\n", dev->recon_tmo);
#endif
	return 0;
}