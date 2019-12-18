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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_SC ; 
 int DID_PARITY ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  done (struct Scsi_Host*,int) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void parerr_run(struct Scsi_Host *shpnt)
{
	scmd_printk(KERN_ERR, CURRENT_SC, "parity error\n");
	done(shpnt, DID_PARITY << 16);
}