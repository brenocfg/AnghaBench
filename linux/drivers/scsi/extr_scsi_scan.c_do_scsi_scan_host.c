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
struct Scsi_Host {TYPE_1__* hostt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* scan_finished ) (struct Scsi_Host*,unsigned long) ;int /*<<< orphan*/  (* scan_start ) (struct Scsi_Host*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_WILD_CARD ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  scsi_scan_host_selected (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub2 (struct Scsi_Host*,unsigned long) ; 

__attribute__((used)) static void do_scsi_scan_host(struct Scsi_Host *shost)
{
	if (shost->hostt->scan_finished) {
		unsigned long start = jiffies;
		if (shost->hostt->scan_start)
			shost->hostt->scan_start(shost);

		while (!shost->hostt->scan_finished(shost, jiffies - start))
			msleep(10);
	} else {
		scsi_scan_host_selected(shost, SCAN_WILD_CARD, SCAN_WILD_CARD,
				SCAN_WILD_CARD, 0);
	}
}