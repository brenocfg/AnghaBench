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
 int CH1 ; 
 int CLRSTCNT ; 
 int /*<<< orphan*/  CMD_INC_RESID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CURRENT_SC ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int /*<<< orphan*/  GETSTCNT () ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SXFRCTL0 ; 

__attribute__((used)) static void datai_end(struct Scsi_Host *shpnt)
{
	CMD_INC_RESID(CURRENT_SC, -GETSTCNT());

	SETPORT(SXFRCTL0, CH1|CLRSTCNT);
	SETPORT(DMACNTRL0, 0);
}