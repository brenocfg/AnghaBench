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
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ MSGOLEN ; 
 scalar_t__ MSGO_I ; 
 int SYNCNEG ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void msgo_end(struct Scsi_Host *shpnt)
{
	if(MSGO_I<MSGOLEN) {
		scmd_printk(KERN_ERR, CURRENT_SC,
			    "message sent incompletely (%d/%d)\n",
			    MSGO_I, MSGOLEN);
		if(SYNCNEG==1) {
			scmd_printk(KERN_INFO, CURRENT_SC,
				    "Synchronous Data Transfer Request was rejected\n");
			SYNCNEG=2;
		}
	}

	MSGO_I  = 0;
	MSGOLEN = 0;
}