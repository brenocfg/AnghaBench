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
typedef  unsigned long u64 ;

/* Variables and functions */
 int MCHK_DISPOSITION_REPORT ; 
 int MCHK_DISPOSITION_UNKNOWN_ERROR ; 

__attribute__((used)) static int
titan_parse_p_agperror(int which, u64 agperror, int print)
{
	int status = MCHK_DISPOSITION_REPORT;
#ifdef CONFIG_VERBOSE_MCHECK
	int cmd, len;
	unsigned long addr;

	static const char * const agperror_cmd[] = {
		"Read (low-priority)",	"Read (high-priority)",
		"Write (low-priority)",	"Write (high-priority)",
		"Reserved",		"Reserved",
		"Flush",		"Fence"
	};
#endif /* CONFIG_VERBOSE_MCHECK */

#define TITAN__PCHIP_AGPERROR__LOST	(1UL << 0)
#define TITAN__PCHIP_AGPERROR__LPQFULL	(1UL << 1)
#define TITAN__PCHIP_AGPERROR__HPQFULL	(1UL << 2)
#define TITAN__PCHIP_AGPERROR__RESCMD	(1UL << 3)
#define TITAN__PCHIP_AGPERROR__IPTE	(1UL << 4)
#define TITAN__PCHIP_AGPERROR__PTP	(1UL << 5)
#define TITAN__PCHIP_AGPERROR__NOWINDOW	(1UL << 6)
#define TITAN__PCHIP_AGPERROR__ERRMASK	(TITAN__PCHIP_AGPERROR__LOST |    \
					 TITAN__PCHIP_AGPERROR__LPQFULL | \
					 TITAN__PCHIP_AGPERROR__HPQFULL | \
					 TITAN__PCHIP_AGPERROR__RESCMD |  \
					 TITAN__PCHIP_AGPERROR__IPTE |    \
					 TITAN__PCHIP_AGPERROR__PTP |     \
					 TITAN__PCHIP_AGPERROR__NOWINDOW)
#define TITAN__PCHIP_AGPERROR__DAC	(1UL << 48)
#define TITAN__PCHIP_AGPERROR__MWIN	(1UL << 49)
#define TITAN__PCHIP_AGPERROR__FENCE	(1UL << 59)
#define TITAN__PCHIP_AGPERROR__CMD__S	(50)
#define TITAN__PCHIP_AGPERROR__CMD__M	(0x07)
#define TITAN__PCHIP_AGPERROR__ADDR__S	(15)
#define TITAN__PCHIP_AGPERROR__ADDR__M  (0xffffffffUL)
#define TITAN__PCHIP_AGPERROR__LEN__S	(53)
#define TITAN__PCHIP_AGPERROR__LEN__M	(0x3f)

	if (!(agperror & TITAN__PCHIP_AGPERROR__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

#ifdef CONFIG_VERBOSE_MCHECK
	if (!print)
		return status;

	cmd = EXTRACT(agperror, TITAN__PCHIP_AGPERROR__CMD);
	addr = EXTRACT(agperror, TITAN__PCHIP_AGPERROR__ADDR) << 3;
	len = EXTRACT(agperror, TITAN__PCHIP_AGPERROR__LEN);

	printk("%s  PChip %d AGPERROR: %016llx\n", err_print_prefix,
	       which, agperror);
	if (agperror & TITAN__PCHIP_AGPERROR__NOWINDOW)
		printk("%s    No Window\n", err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__PTP)
		printk("%s    Peer-to-Peer set\n", err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__IPTE)
		printk("%s    Invalid PTE\n", err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__RESCMD)
		printk("%s    Reserved Command\n", err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__HPQFULL)
		printk("%s    HP Transaction Received while Queue Full\n", 
		       err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__LPQFULL)
		printk("%s    LP Transaction Received while Queue Full\n", 
		       err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__LOST)
		printk("%s    Lost Error\n", err_print_prefix);
	printk("%s      Command: 0x%x - %s, %d Quadwords%s\n"
		 "      Address: 0x%lx\n",
	       err_print_prefix, cmd, agperror_cmd[cmd], len,
	       (agperror & TITAN__PCHIP_AGPERROR__FENCE) ? ", FENCE" : "",
	       addr);
	if (agperror & TITAN__PCHIP_AGPERROR__DAC)
		printk("%s      Dual Address Cycle\n", err_print_prefix);
	if (agperror & TITAN__PCHIP_AGPERROR__MWIN)
		printk("%s      Hit in Monster Window\n", err_print_prefix);
#endif /* CONFIG_VERBOSE_MCHECK */

	return status;
}