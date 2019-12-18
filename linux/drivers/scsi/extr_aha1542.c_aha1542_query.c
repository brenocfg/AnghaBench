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
typedef  int u8 ;
struct aha1542_hostdata {int /*<<< orphan*/  bios_translation; } ;
struct Scsi_Host {int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_TRANSLATION_6432 ; 
 int /*<<< orphan*/  CMD_INQUIRY ; 
 int /*<<< orphan*/  DATA (int /*<<< orphan*/ ) ; 
 int DF ; 
 int /*<<< orphan*/  HACC ; 
 int /*<<< orphan*/  INTRFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTRMASK ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_in (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_intr_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aha1542_mbenable (struct Scsi_Host*) ; 
 int /*<<< orphan*/  aha1542_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 struct aha1542_hostdata* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  wait_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aha1542_query(struct Scsi_Host *sh)
{
	struct aha1542_hostdata *aha1542 = shost_priv(sh);
	u8 inquiry_result[4];
	int i;
	i = inb(STATUS(sh->io_port));
	if (i & DF) {
		i = inb(DATA(sh->io_port));
	};
	aha1542_outb(sh->io_port, CMD_INQUIRY);
	aha1542_in(sh->io_port, inquiry_result, 4, 0);
	if (!wait_mask(INTRFLAGS(sh->io_port), INTRMASK, HACC, 0, 0))
		shost_printk(KERN_ERR, sh, "error querying card type\n");
	aha1542_intr_reset(sh->io_port);

	aha1542->bios_translation = BIOS_TRANSLATION_6432;	/* Default case */

	/* For an AHA1740 series board, we ignore the board since there is a
	   hardware bug which can lead to wrong blocks being returned if the board
	   is operating in the 1542 emulation mode.  Since there is an extended mode
	   driver, we simply ignore the board and let the 1740 driver pick it up.
	 */

	if (inquiry_result[0] == 0x43) {
		shost_printk(KERN_INFO, sh, "Emulation mode not supported for AHA-1740 hardware, use aha1740 driver instead.\n");
		return 1;
	};

	/* Always call this - boards that do not support extended bios translation
	   will ignore the command, and we will set the proper default */

	aha1542->bios_translation = aha1542_mbenable(sh);

	return 0;
}