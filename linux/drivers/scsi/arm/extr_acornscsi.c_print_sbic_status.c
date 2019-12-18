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

/* Variables and functions */
 int ASR_BSY ; 
 int ASR_CIP ; 
 int ASR_DBR ; 
 int ASR_INT ; 
 int ASR_LCI ; 
 int ASR_PE ; 
 int /*<<< orphan*/  print_scsi_status (int) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static
void print_sbic_status(int asr, int ssr, int cmdphase)
{
#ifdef CONFIG_ACORNSCSI_CONSTANTS
    printk("sbic: %c%c%c%c%c%c ",
	    asr & ASR_INT ? 'I' : 'i',
	    asr & ASR_LCI ? 'L' : 'l',
	    asr & ASR_BSY ? 'B' : 'b',
	    asr & ASR_CIP ? 'C' : 'c',
	    asr & ASR_PE  ? 'P' : 'p',
	    asr & ASR_DBR ? 'D' : 'd');
    printk("scsi: ");
    print_scsi_status(ssr);
    printk(" ph %02X\n", cmdphase);
#else
    printk("sbic: %02X scsi: %X:%X ph: %02X\n",
	    asr, (ssr & 0xf0)>>4, ssr & 0x0f, cmdphase);
#endif
}