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
struct ext_code {int subcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQEXT_FTP ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diag_ftp_rx_complete ; 
 int diag_ftp_subcode ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void diag_ftp_handler(struct ext_code extirq,
			     unsigned int param32,
			     unsigned long param64)
{
	if ((extirq.subcode >> 8) != 8)
		return; /* not a FTP services sub-code */

	inc_irq_stat(IRQEXT_FTP);
	diag_ftp_subcode = extirq.subcode & 0xffU;
	complete(&diag_ftp_rx_complete);
}