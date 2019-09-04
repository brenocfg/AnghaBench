#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {char nr; int state; int /*<<< orphan*/  Flags; } ;
struct hscx_hw {int slot; TYPE_1__ bch; TYPE_2__* ip; } ;
struct TYPE_4__ {int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  FLG_HDLC ; 
 int /*<<< orphan*/  FLG_TRANSPARENT ; 
 int IPACX_B_ON ; 
 int /*<<< orphan*/  IPACX_EXMB ; 
 int /*<<< orphan*/  IPACX_MASKB ; 
 int /*<<< orphan*/  IPACX_MODEB ; 
 int /*<<< orphan*/  IPAC_CCR1 ; 
 int /*<<< orphan*/  IPAC_CCR2 ; 
 int /*<<< orphan*/  IPAC_MASKB ; 
 int /*<<< orphan*/  IPAC_MODEB ; 
 int /*<<< orphan*/  IPAC_RCCR ; 
 int /*<<< orphan*/  IPAC_TSAR ; 
 int /*<<< orphan*/  IPAC_TSAX ; 
 int IPAC_TYPE_HSCX ; 
 int IPAC_TYPE_IPAC ; 
 int IPAC_TYPE_IPACX ; 
 int /*<<< orphan*/  IPAC_XCCR ; 
 int /*<<< orphan*/  ISACX_BCHA_CR ; 
 int /*<<< orphan*/  ISACX_BCHA_TSDP_BC1 ; 
 int /*<<< orphan*/  ISACX_BCHB_CR ; 
 int /*<<< orphan*/  ISACX_BCHB_TSDP_BC1 ; 
#define  ISDN_P_B_HDLC 130 
#define  ISDN_P_B_RAW 129 
#define  ISDN_P_NONE 128 
 int /*<<< orphan*/  WriteHSCX (struct hscx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteIPAC (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hscx_cmdr (struct hscx_hw*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,char,int,int,char) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hscx_mode(struct hscx_hw *hscx, u32 bprotocol)
{
	pr_debug("%s: HSCX %c protocol %x-->%x ch %d\n", hscx->ip->name,
		 '@' + hscx->bch.nr, hscx->bch.state, bprotocol, hscx->bch.nr);
	if (hscx->ip->type & IPAC_TYPE_IPACX) {
		if (hscx->bch.nr & 1) { /* B1 and ICA */
			WriteIPAC(hscx->ip, ISACX_BCHA_TSDP_BC1, 0x80);
			WriteIPAC(hscx->ip, ISACX_BCHA_CR, 0x88);
		} else { /* B2 and ICB */
			WriteIPAC(hscx->ip, ISACX_BCHB_TSDP_BC1, 0x81);
			WriteIPAC(hscx->ip, ISACX_BCHB_CR, 0x88);
		}
		switch (bprotocol) {
		case ISDN_P_NONE: /* init */
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* rec off */
			WriteHSCX(hscx, IPACX_EXMB,  0x30);	/* std adj. */
			WriteHSCX(hscx, IPACX_MASKB, 0xFF);	/* ints off */
			hscx_cmdr(hscx, 0x41);
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPACX_MODEB, 0x88);	/* ex trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* trans */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPACX_MODEB, 0xC0);	/* trans */
			WriteHSCX(hscx, IPACX_EXMB,  0x00);	/* hdlc,crc */
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPACX_MASKB, IPACX_B_ON);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else if (hscx->ip->type & IPAC_TYPE_IPAC) { /* IPAC */
		WriteHSCX(hscx, IPAC_CCR1, 0x82);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		switch (bprotocol) {
		case ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x82);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8a);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else if (hscx->ip->type & IPAC_TYPE_HSCX) { /* HSCX */
		WriteHSCX(hscx, IPAC_CCR1, 0x85);
		WriteHSCX(hscx, IPAC_CCR2, 0x30);
		WriteHSCX(hscx, IPAC_XCCR, 0x07);
		WriteHSCX(hscx, IPAC_RCCR, 0x07);
		WriteHSCX(hscx, IPAC_TSAX, hscx->slot);
		WriteHSCX(hscx, IPAC_TSAR, hscx->slot);
		switch (bprotocol) {
		case ISDN_P_NONE:
			WriteHSCX(hscx, IPAC_TSAX, 0x1F);
			WriteHSCX(hscx, IPAC_TSAR, 0x1F);
			WriteHSCX(hscx, IPAC_MODEB, 0x84);
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			WriteHSCX(hscx, IPAC_MASKB, 0xFF);	/* ints off */
			test_and_clear_bit(FLG_HDLC, &hscx->bch.Flags);
			test_and_clear_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_RAW:
			WriteHSCX(hscx, IPAC_MODEB, 0xe4);	/* ex trans */
			WriteHSCX(hscx, IPAC_CCR1, 0x85);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_TRANSPARENT, &hscx->bch.Flags);
			break;
		case ISDN_P_B_HDLC:
			WriteHSCX(hscx, IPAC_MODEB, 0x8c);
			WriteHSCX(hscx, IPAC_CCR1, 0x8d);
			hscx_cmdr(hscx, 0x41);
			WriteHSCX(hscx, IPAC_MASKB, 0);
			test_and_set_bit(FLG_HDLC, &hscx->bch.Flags);
			break;
		default:
			pr_info("%s: protocol not known %x\n", hscx->ip->name,
				bprotocol);
			return -ENOPROTOOPT;
		}
	} else
		return -EINVAL;
	hscx->bch.state = bprotocol;
	return 0;
}