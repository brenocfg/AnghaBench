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
typedef  int u32 ;
struct sym_hcb {int features; int mmio_ba; int scripta_ba; int scriptb_ba; int hcb_ba; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_SCRIPT ; 
 int FE_PFEN ; 
 int FE_WIDE ; 
 int OPC_MOVE ; 
 int OPC_TCHMOVE ; 
#define  RELOC_LABEL_A 131 
#define  RELOC_LABEL_B 130 
 int RELOC_MASK ; 
#define  RELOC_REGISTER 129 
#define  RELOC_SOFTC 128 
 int SCR_DATA_ZERO ; 
 int SCR_NO_FLUSH ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* sym_name (struct sym_hcb*) ; 

void sym_fw_bind_script(struct sym_hcb *np, u32 *start, int len)
{
	u32 opcode, new, old, tmp1, tmp2;
	u32 *end, *cur;
	int relocs;

	cur = start;
	end = start + len/4;

	while (cur < end) {

		opcode = *cur;

		/*
		 *  If we forget to change the length
		 *  in scripts, a field will be
		 *  padded with 0. This is an illegal
		 *  command.
		 */
		if (opcode == 0) {
			printf ("%s: ERROR0 IN SCRIPT at %d.\n",
				sym_name(np), (int) (cur-start));
			++cur;
			continue;
		};

		/*
		 *  We use the bogus value 0xf00ff00f ;-)
		 *  to reserve data area in SCRIPTS.
		 */
		if (opcode == SCR_DATA_ZERO) {
			*cur++ = 0;
			continue;
		}

		if (DEBUG_FLAGS & DEBUG_SCRIPT)
			printf ("%d:  <%x>\n", (int) (cur-start),
				(unsigned)opcode);

		/*
		 *  We don't have to decode ALL commands
		 */
		switch (opcode >> 28) {
		case 0xf:
			/*
			 *  LOAD / STORE DSA relative, don't relocate.
			 */
			relocs = 0;
			break;
		case 0xe:
			/*
			 *  LOAD / STORE absolute.
			 */
			relocs = 1;
			break;
		case 0xc:
			/*
			 *  COPY has TWO arguments.
			 */
			relocs = 2;
			tmp1 = cur[1];
			tmp2 = cur[2];
			if ((tmp1 ^ tmp2) & 3) {
				printf ("%s: ERROR1 IN SCRIPT at %d.\n",
					sym_name(np), (int) (cur-start));
			}
			/*
			 *  If PREFETCH feature not enabled, remove 
			 *  the NO FLUSH bit if present.
			 */
			if ((opcode & SCR_NO_FLUSH) &&
			    !(np->features & FE_PFEN)) {
				opcode = (opcode & ~SCR_NO_FLUSH);
			}
			break;
		case 0x0:
			/*
			 *  MOVE/CHMOV (absolute address)
			 */
			if (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 1;
			break;
		case 0x1:
			/*
			 *  MOVE/CHMOV (table indirect)
			 */
			if (!(np->features & FE_WIDE))
				opcode = (opcode | OPC_MOVE);
			relocs = 0;
			break;
#ifdef SYM_CONF_TARGET_ROLE_SUPPORT
		case 0x2:
			/*
			 *  MOVE/CHMOV in target role (absolute address)
			 */
			opcode &= ~0x20000000;
			if (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 1;
			break;
		case 0x3:
			/*
			 *  MOVE/CHMOV in target role (table indirect)
			 */
			opcode &= ~0x20000000;
			if (!(np->features & FE_WIDE))
				opcode = (opcode & ~OPC_TCHMOVE);
			relocs = 0;
			break;
#endif
		case 0x8:
			/*
			 *  JUMP / CALL
			 *  don't relocate if relative :-)
			 */
			if (opcode & 0x00800000)
				relocs = 0;
			else if ((opcode & 0xf8400000) == 0x80400000)/*JUMP64*/
				relocs = 2;
			else
				relocs = 1;
			break;
		case 0x4:
		case 0x5:
		case 0x6:
		case 0x7:
			relocs = 1;
			break;
		default:
			relocs = 0;
			break;
		};

		/*
		 *  Scriptify:) the opcode.
		 */
		*cur++ = cpu_to_scr(opcode);

		/*
		 *  If no relocation, assume 1 argument 
		 *  and just scriptize:) it.
		 */
		if (!relocs) {
			*cur = cpu_to_scr(*cur);
			++cur;
			continue;
		}

		/*
		 *  Otherwise performs all needed relocations.
		 */
		while (relocs--) {
			old = *cur;

			switch (old & RELOC_MASK) {
			case RELOC_REGISTER:
				new = (old & ~RELOC_MASK) + np->mmio_ba;
				break;
			case RELOC_LABEL_A:
				new = (old & ~RELOC_MASK) + np->scripta_ba;
				break;
			case RELOC_LABEL_B:
				new = (old & ~RELOC_MASK) + np->scriptb_ba;
				break;
			case RELOC_SOFTC:
				new = (old & ~RELOC_MASK) + np->hcb_ba;
				break;
			case 0:
				/*
				 *  Don't relocate a 0 address.
				 *  They are mostly used for patched or 
				 *  script self-modified areas.
				 */
				if (old == 0) {
					new = old;
					break;
				}
				/* fall through */
			default:
				new = 0;
				panic("sym_fw_bind_script: "
				      "weird relocation %x\n", old);
				break;
			}

			*cur++ = cpu_to_scr(new);
		}
	};
}