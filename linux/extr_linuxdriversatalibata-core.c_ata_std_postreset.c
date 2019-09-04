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
typedef  int /*<<< orphan*/  u32 ;
struct ata_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  SCR_ERROR ; 
 int /*<<< orphan*/  sata_print_link_status (struct ata_link*) ; 
 int /*<<< orphan*/  sata_scr_read (struct ata_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sata_scr_write (struct ata_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ata_std_postreset(struct ata_link *link, unsigned int *classes)
{
	u32 serror;

	DPRINTK("ENTER\n");

	/* reset complete, clear SError */
	if (!sata_scr_read(link, SCR_ERROR, &serror))
		sata_scr_write(link, SCR_ERROR, serror);

	/* print link status */
	sata_print_link_status(link);

	DPRINTK("EXIT\n");
}