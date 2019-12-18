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
 int /*<<< orphan*/  CURRENT_SC ; 
 int /*<<< orphan*/  DATA_LEN ; 
 int /*<<< orphan*/  DMACNTRL0 ; 
 int DMAEN ; 
 int ENBUSFREE ; 
 int ENDMA ; 
 int ENPHASEMIS ; 
 int ENSCSIPERR ; 
 int ENSCSIRST ; 
 int RSTFIFO ; 
 int SCSIEN ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int /*<<< orphan*/  SXFRCTL0 ; 
 int WRITE_READ ; 
 int /*<<< orphan*/  scsi_get_resid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void datao_init(struct Scsi_Host *shpnt)
{
	SETPORT(DMACNTRL0, WRITE_READ | RSTFIFO);
	SETPORT(DMACNTRL0, WRITE_READ | ENDMA);

	SETPORT(SXFRCTL0, CH1|CLRSTCNT);
	SETPORT(SXFRCTL0, CH1|SCSIEN|DMAEN);

	SETPORT(SIMODE0, 0);
	SETPORT(SIMODE1, ENSCSIPERR | ENSCSIRST | ENPHASEMIS | ENBUSFREE );

	DATA_LEN = scsi_get_resid(CURRENT_SC);
}