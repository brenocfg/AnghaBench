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
struct de4x5_private {int chipset; int useSROM; int /*<<< orphan*/  srom; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DC21040 ; 
 int DC21041 ; 
 int DC21140 ; 
 int DC21142 ; 
 int DC21143 ; 
 int DC2114x ; 
 int /*<<< orphan*/ * de4x5_signatures ; 
 scalar_t__ dec_only ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
PCI_signature(char *name, struct de4x5_private *lp)
{
    int i, status = 0, siglen = ARRAY_SIZE(de4x5_signatures);

    if (lp->chipset == DC21040) {
	strcpy(name, "DE434/5");
	return status;
    } else {                           /* Search for a DEC name in the SROM */
	int tmp = *((char *)&lp->srom + 19) * 3;
	strncpy(name, (char *)&lp->srom + 26 + tmp, 8);
    }
    name[8] = '\0';
    for (i=0; i<siglen; i++) {
	if (strstr(name,de4x5_signatures[i])!=NULL) break;
    }
    if (i == siglen) {
	if (dec_only) {
	    *name = '\0';
	} else {                        /* Use chip name to avoid confusion */
	    strcpy(name, (((lp->chipset == DC21040) ? "DC21040" :
			   ((lp->chipset == DC21041) ? "DC21041" :
			    ((lp->chipset == DC21140) ? "DC21140" :
			     ((lp->chipset == DC21142) ? "DC21142" :
			      ((lp->chipset == DC21143) ? "DC21143" : "UNKNOWN"
			     )))))));
	}
	if (lp->chipset != DC21041) {
	    lp->useSROM = true;             /* card is not recognisably DEC */
	}
    } else if ((lp->chipset & ~0x00ff) == DC2114x) {
	lp->useSROM = true;
    }

    return status;
}