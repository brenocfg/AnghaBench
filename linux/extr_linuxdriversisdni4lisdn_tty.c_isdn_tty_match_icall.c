#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* lmsn; char* msn; } ;
typedef  TYPE_1__ atemu ;

/* Variables and functions */
 int /*<<< orphan*/  isdn_map_eaz2msn (char*,int) ; 
 int isdn_msncmp (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int
isdn_tty_match_icall(char *cid, atemu *emu, int di)
{
#ifdef ISDN_DEBUG_MODEM_ICALL
	printk(KERN_DEBUG "m_fi: msn=%s lmsn=%s mmsn=%s mreg[SI1]=%d mreg[SI2]=%d\n",
	       emu->msn, emu->lmsn, isdn_map_eaz2msn(emu->msn, di),
	       emu->mdmreg[REG_SI1], emu->mdmreg[REG_SI2]);
#endif
	if (strlen(emu->lmsn)) {
		char *p = emu->lmsn;
		char *q;
		int  tmp;
		int  ret = 0;

		while (1) {
			if ((q = strchr(p, ';')))
				*q = '\0';
			if ((tmp = isdn_msncmp(cid, isdn_map_eaz2msn(p, di))) > ret)
				ret = tmp;
#ifdef ISDN_DEBUG_MODEM_ICALL
			printk(KERN_DEBUG "m_fi: lmsnX=%s mmsn=%s -> tmp=%d\n",
			       p, isdn_map_eaz2msn(emu->msn, di), tmp);
#endif
			if (q) {
				*q = ';';
				p = q;
				p++;
			}
			if (!tmp)
				return 0;
			if (!q)
				break;
		}
		return ret;
	} else {
		int tmp;
		tmp = isdn_msncmp(cid, isdn_map_eaz2msn(emu->msn, di));
#ifdef ISDN_DEBUG_MODEM_ICALL
		printk(KERN_DEBUG "m_fi: mmsn=%s -> tmp=%d\n",
		       isdn_map_eaz2msn(emu->msn, di), tmp);
#endif
		return tmp;
	}
}