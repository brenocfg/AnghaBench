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
titan_parse_c_misc(u64 c_misc, int print)
{
#ifdef CONFIG_VERBOSE_MCHECK
	char *src;
	int nxs = 0;
#endif
	int status = MCHK_DISPOSITION_REPORT;

#define TITAN__CCHIP_MISC__NXM		(1UL << 28)
#define TITAN__CCHIP_MISC__NXS__S	(29)
#define TITAN__CCHIP_MISC__NXS__M	(0x7)

	if (!(c_misc & TITAN__CCHIP_MISC__NXM))
		return MCHK_DISPOSITION_UNKNOWN_ERROR;

#ifdef CONFIG_VERBOSE_MCHECK
	if (!print)
		return status;

	nxs = EXTRACT(c_misc, TITAN__CCHIP_MISC__NXS);
	switch(nxs) {
	case 0:	/* CPU 0 */
	case 1:	/* CPU 1 */
	case 2:	/* CPU 2 */
	case 3:	/* CPU 3 */
		src = "CPU";
		/* num is already the CPU number */
		break;
	case 4:	/* Pchip 0 */
	case 5:	/* Pchip 1 */
		src = "Pchip";
		nxs -= 4;
		break;
	default:/* reserved */
		src = "Unknown, NXS =";
		/* leave num untouched */
		break;
	}

	printk("%s    Non-existent memory access from: %s %d\n", 
	       err_print_prefix, src, nxs);
#endif /* CONFIG_VERBOSE_MCHECK */

	return status;
}