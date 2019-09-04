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
typedef  int u16 ;

/* Variables and functions */
 unsigned long BAD_INSTR ; 

__attribute__((used)) static unsigned long
thumb2arm(u16 tinstr)
{
	u32 L = (tinstr & (1<<11)) >> 11;

	switch ((tinstr & 0xf800) >> 11) {
	/* 6.5.1 Format 1: */
	case 0x6000 >> 11:				/* 7.1.52 STR(1) */
	case 0x6800 >> 11:				/* 7.1.26 LDR(1) */
	case 0x7000 >> 11:				/* 7.1.55 STRB(1) */
	case 0x7800 >> 11:				/* 7.1.30 LDRB(1) */
		return 0xe5800000 |
			((tinstr & (1<<12)) << (22-12)) |	/* fixup */
			(L<<20) |				/* L==1? */
			((tinstr & (7<<0)) << (12-0)) |		/* Rd */
			((tinstr & (7<<3)) << (16-3)) |		/* Rn */
			((tinstr & (31<<6)) >>			/* immed_5 */
				(6 - ((tinstr & (1<<12)) ? 0 : 2)));
	case 0x8000 >> 11:				/* 7.1.57 STRH(1) */
	case 0x8800 >> 11:				/* 7.1.32 LDRH(1) */
		return 0xe1c000b0 |
			(L<<20) |				/* L==1? */
			((tinstr & (7<<0)) << (12-0)) |		/* Rd */
			((tinstr & (7<<3)) << (16-3)) |		/* Rn */
			((tinstr & (7<<6)) >> (6-1)) |	 /* immed_5[2:0] */
			((tinstr & (3<<9)) >> (9-8));	 /* immed_5[4:3] */

	/* 6.5.1 Format 2: */
	case 0x5000 >> 11:
	case 0x5800 >> 11:
		{
			static const u32 subset[8] = {
				0xe7800000,		/* 7.1.53 STR(2) */
				0xe18000b0,		/* 7.1.58 STRH(2) */
				0xe7c00000,		/* 7.1.56 STRB(2) */
				0xe19000d0,		/* 7.1.34 LDRSB */
				0xe7900000,		/* 7.1.27 LDR(2) */
				0xe19000b0,		/* 7.1.33 LDRH(2) */
				0xe7d00000,		/* 7.1.31 LDRB(2) */
				0xe19000f0		/* 7.1.35 LDRSH */
			};
			return subset[(tinstr & (7<<9)) >> 9] |
			    ((tinstr & (7<<0)) << (12-0)) |	/* Rd */
			    ((tinstr & (7<<3)) << (16-3)) |	/* Rn */
			    ((tinstr & (7<<6)) >> (6-0));	/* Rm */
		}

	/* 6.5.1 Format 3: */
	case 0x4800 >> 11:				/* 7.1.28 LDR(3) */
		/* NOTE: This case is not technically possible. We're
		 *	 loading 32-bit memory data via PC relative
		 *	 addressing mode. So we can and should eliminate
		 *	 this case. But I'll leave it here for now.
		 */
		return 0xe59f0000 |
		    ((tinstr & (7<<8)) << (12-8)) |		/* Rd */
		    ((tinstr & 255) << (2-0));			/* immed_8 */

	/* 6.5.1 Format 4: */
	case 0x9000 >> 11:				/* 7.1.54 STR(3) */
	case 0x9800 >> 11:				/* 7.1.29 LDR(4) */
		return 0xe58d0000 |
			(L<<20) |				/* L==1? */
			((tinstr & (7<<8)) << (12-8)) |		/* Rd */
			((tinstr & 255) << 2);			/* immed_8 */

	/* 6.6.1 Format 1: */
	case 0xc000 >> 11:				/* 7.1.51 STMIA */
	case 0xc800 >> 11:				/* 7.1.25 LDMIA */
		{
			u32 Rn = (tinstr & (7<<8)) >> 8;
			u32 W = ((L<<Rn) & (tinstr&255)) ? 0 : 1<<21;

			return 0xe8800000 | W | (L<<20) | (Rn<<16) |
				(tinstr&255);
		}

	/* 6.6.1 Format 2: */
	case 0xb000 >> 11:				/* 7.1.48 PUSH */
	case 0xb800 >> 11:				/* 7.1.47 POP */
		if ((tinstr & (3 << 9)) == 0x0400) {
			static const u32 subset[4] = {
				0xe92d0000,	/* STMDB sp!,{registers} */
				0xe92d4000,	/* STMDB sp!,{registers,lr} */
				0xe8bd0000,	/* LDMIA sp!,{registers} */
				0xe8bd8000	/* LDMIA sp!,{registers,pc} */
			};
			return subset[(L<<1) | ((tinstr & (1<<8)) >> 8)] |
			    (tinstr & 255);		/* register_list */
		}
		/* Else fall through for illegal instruction case */

	default:
		return BAD_INSTR;
	}
}