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
 int ENATNTARG ; 
 int ENBUSFREE ; 
 int ENDMADONE ; 
 int ENPHASECHG ; 
 int ENPHASEMIS ; 
 int ENREQINIT ; 
 int ENSCSIPERR ; 
 int ENSDONE ; 
 int ENSELDI ; 
 int ENSELDO ; 
 int ENSELINGO ; 
 int ENSELTIMO ; 
 int ENSPIORDY ; 
 int ENSWRAP ; 
 int GETPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  SIMODE0 ; 
 int /*<<< orphan*/  SIMODE1 ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void disp_enintr(struct Scsi_Host *shpnt)
{
	int s0, s1;

	s0 = GETPORT(SIMODE0);
	s1 = GETPORT(SIMODE1);

	shost_printk(KERN_DEBUG, shpnt,
		     "enabled interrupts (%s%s%s%s%s%s%s%s%s%s%s%s%s%s)\n",
		     (s0 & ENSELDO) ? "ENSELDO " : "",
		     (s0 & ENSELDI) ? "ENSELDI " : "",
		     (s0 & ENSELINGO) ? "ENSELINGO " : "",
		     (s0 & ENSWRAP) ? "ENSWRAP " : "",
		     (s0 & ENSDONE) ? "ENSDONE " : "",
		     (s0 & ENSPIORDY) ? "ENSPIORDY " : "",
		     (s0 & ENDMADONE) ? "ENDMADONE " : "",
		     (s1 & ENSELTIMO) ? "ENSELTIMO " : "",
		     (s1 & ENATNTARG) ? "ENATNTARG " : "",
		     (s1 & ENPHASEMIS) ? "ENPHASEMIS " : "",
		     (s1 & ENBUSFREE) ? "ENBUSFREE " : "",
		     (s1 & ENSCSIPERR) ? "ENSCSIPERR " : "",
		     (s1 & ENPHASECHG) ? "ENPHASECHG " : "",
		     (s1 & ENREQINIT) ? "ENREQINIT " : "");
}