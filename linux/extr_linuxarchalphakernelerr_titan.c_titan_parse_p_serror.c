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
titan_parse_p_serror(int which, u64 serror, int print)
{
	int status = MCHK_DISPOSITION_REPORT;

#ifdef CONFIG_VERBOSE_MCHECK
	static const char * const serror_src[] = {
		"GPCI", "APCI", "AGP HP", "AGP LP"
	};
	static const char * const serror_cmd[] = {
		"DMA Read", "DMA RMW", "SGTE Read", "Reserved"
	};
#endif /* CONFIG_VERBOSE_MCHECK */

#define TITAN__PCHIP_SERROR__LOST_UECC	(1UL << 0)
#define TITAN__PCHIP_SERROR__UECC	(1UL << 1)
#define TITAN__PCHIP_SERROR__CRE	(1UL << 2)
#define TITAN__PCHIP_SERROR__NXIO	(1UL << 3)
#define TITAN__PCHIP_SERROR__LOST_CRE	(1UL << 4)
#define TITAN__PCHIP_SERROR__ECCMASK	(TITAN__PCHIP_SERROR__UECC |	  \
					 TITAN__PCHIP_SERROR__CRE)
#define TITAN__PCHIP_SERROR__ERRMASK	(TITAN__PCHIP_SERROR__LOST_UECC | \
					 TITAN__PCHIP_SERROR__UECC |	  \
					 TITAN__PCHIP_SERROR__CRE |	  \
					 TITAN__PCHIP_SERROR__NXIO |	  \
					 TITAN__PCHIP_SERROR__LOST_CRE)
#define TITAN__PCHIP_SERROR__SRC__S	(52)
#define TITAN__PCHIP_SERROR__SRC__M	(0x3)
#define TITAN__PCHIP_SERROR__CMD__S	(54)
#define TITAN__PCHIP_SERROR__CMD__M	(0x3)
#define TITAN__PCHIP_SERROR__SYN__S	(56)
#define TITAN__PCHIP_SERROR__SYN__M	(0xff)
#define TITAN__PCHIP_SERROR__ADDR__S	(15)
#define TITAN__PCHIP_SERROR__ADDR__M	(0xffffffffUL)

	if (!(serror & TITAN__PCHIP_SERROR__ERRMASK))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

#ifdef CONFIG_VERBOSE_MCHECK
	if (!print)
		return status;

	printk("%s  PChip %d SERROR: %016llx\n",
	       err_print_prefix, which, serror);
	if (serror & TITAN__PCHIP_SERROR__ECCMASK) {
		printk("%s    %sorrectable ECC Error:\n"
		       "      Source: %-6s  Command: %-8s  Syndrome: 0x%08x\n"
		       "      Address: 0x%llx\n",
		       err_print_prefix,
		       (serror & TITAN__PCHIP_SERROR__UECC) ? "Unc" : "C",
		       serror_src[EXTRACT(serror, TITAN__PCHIP_SERROR__SRC)],
		       serror_cmd[EXTRACT(serror, TITAN__PCHIP_SERROR__CMD)],
		       (unsigned)EXTRACT(serror, TITAN__PCHIP_SERROR__SYN),
		       EXTRACT(serror, TITAN__PCHIP_SERROR__ADDR));
	}
	if (serror & TITAN__PCHIP_SERROR__NXIO)
		printk("%s    Non Existent I/O Error\n", err_print_prefix);
	if (serror & TITAN__PCHIP_SERROR__LOST_UECC)
		printk("%s    Lost Uncorrectable ECC Error\n", 
		       err_print_prefix);
	if (serror & TITAN__PCHIP_SERROR__LOST_CRE)
		printk("%s    Lost Correctable ECC Error\n", err_print_prefix);
#endif /* CONFIG_VERBOSE_MCHECK */

	return status;
}