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
typedef  int u16 ;

/* Variables and functions */
 int FIXUP_BRANCH_NOT_TAKEN ; 
 int FIXUP_NOT_REQUIRED ; 
 int FIXUP_PSW_NORMAL ; 
 int FIXUP_RETURN_REGISTER ; 

int probe_get_fixup_type(u16 *insn)
{
	/* default fixup method */
	int fixup = FIXUP_PSW_NORMAL;

	switch (insn[0] >> 8) {
	case 0x05:	/* balr	*/
	case 0x0d:	/* basr */
		fixup = FIXUP_RETURN_REGISTER;
		/* if r2 = 0, no branch will be taken */
		if ((insn[0] & 0x0f) == 0)
			fixup |= FIXUP_BRANCH_NOT_TAKEN;
		break;
	case 0x06:	/* bctr	*/
	case 0x07:	/* bcr	*/
		fixup = FIXUP_BRANCH_NOT_TAKEN;
		break;
	case 0x45:	/* bal	*/
	case 0x4d:	/* bas	*/
		fixup = FIXUP_RETURN_REGISTER;
		break;
	case 0x47:	/* bc	*/
	case 0x46:	/* bct	*/
	case 0x86:	/* bxh	*/
	case 0x87:	/* bxle	*/
		fixup = FIXUP_BRANCH_NOT_TAKEN;
		break;
	case 0x82:	/* lpsw	*/
		fixup = FIXUP_NOT_REQUIRED;
		break;
	case 0xb2:	/* lpswe */
		if ((insn[0] & 0xff) == 0xb2)
			fixup = FIXUP_NOT_REQUIRED;
		break;
	case 0xa7:	/* bras	*/
		if ((insn[0] & 0x0f) == 0x05)
			fixup |= FIXUP_RETURN_REGISTER;
		break;
	case 0xc0:
		if ((insn[0] & 0x0f) == 0x05)	/* brasl */
			fixup |= FIXUP_RETURN_REGISTER;
		break;
	case 0xeb:
		switch (insn[2] & 0xff) {
		case 0x44: /* bxhg  */
		case 0x45: /* bxleg */
			fixup = FIXUP_BRANCH_NOT_TAKEN;
			break;
		}
		break;
	case 0xe3:	/* bctg	*/
		if ((insn[2] & 0xff) == 0x46)
			fixup = FIXUP_BRANCH_NOT_TAKEN;
		break;
	case 0xec:
		switch (insn[2] & 0xff) {
		case 0xe5: /* clgrb */
		case 0xe6: /* cgrb  */
		case 0xf6: /* crb   */
		case 0xf7: /* clrb  */
		case 0xfc: /* cgib  */
		case 0xfd: /* cglib */
		case 0xfe: /* cib   */
		case 0xff: /* clib  */
			fixup = FIXUP_BRANCH_NOT_TAKEN;
			break;
		}
		break;
	}
	return fixup;
}