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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int HRST ; 
 int SCRST ; 
 int aha1542_reset (struct scsi_cmnd*,int) ; 

__attribute__((used)) static int aha1542_host_reset(struct scsi_cmnd *cmd)
{
	return aha1542_reset(cmd, HRST | SCRST);
}