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
struct device {int dummy; } ;

/* Variables and functions */
#define  REG_ACKTMOUT 183 
#define  REG_BBREG0 182 
#define  REG_BBREG1 181 
#define  REG_BBREG2 180 
#define  REG_BBREG3 179 
#define  REG_BBREG4 178 
#define  REG_BBREG6 177 
#define  REG_CCAEDTH 176 
#define  REG_EADR0 175 
#define  REG_EADR1 174 
#define  REG_EADR2 173 
#define  REG_EADR3 172 
#define  REG_EADR4 171 
#define  REG_EADR5 170 
#define  REG_EADR6 169 
#define  REG_EADR7 168 
#define  REG_ESLOTG1 167 
#define  REG_ESLOTG23 166 
#define  REG_ESLOTG45 165 
#define  REG_ESLOTG67 164 
#define  REG_FROMOFFSET 163 
#define  REG_GATECLK 162 
#define  REG_GPIO 161 
#define  REG_HSYMTMRH 160 
#define  REG_HSYMTMRL 159 
#define  REG_INTCON 158 
#define  REG_ORDER 157 
#define  REG_PACON0 156 
#define  REG_PACON1 155 
#define  REG_PACON2 154 
#define  REG_PANIDH 153 
#define  REG_PANIDL 152 
#define  REG_RFCTL 151 
#define  REG_RXFLUSH 150 
#define  REG_RXMCR 149 
#define  REG_RXSR 148 
#define  REG_SADRH 147 
#define  REG_SADRL 146 
#define  REG_SECCON0 145 
#define  REG_SECCON1 144 
#define  REG_SECCR2 143 
#define  REG_SLPACK 142 
#define  REG_SOFTRST 141 
#define  REG_SYMTICKH 140 
#define  REG_SYMTICKL 139 
#define  REG_TRISGPIO 138 
#define  REG_TXBCON0 137 
#define  REG_TXBCON1 136 
#define  REG_TXG1CON 135 
#define  REG_TXG2CON 134 
#define  REG_TXMCR 133 
#define  REG_TXNCON 132 
#define  REG_TXPEND 131 
#define  REG_TXSTBL 130 
#define  REG_TXTIME 129 
#define  REG_WAKECON 128 

__attribute__((used)) static bool
mrf24j40_short_reg_writeable(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case REG_RXMCR:
	case REG_PANIDL:
	case REG_PANIDH:
	case REG_SADRL:
	case REG_SADRH:
	case REG_EADR0:
	case REG_EADR1:
	case REG_EADR2:
	case REG_EADR3:
	case REG_EADR4:
	case REG_EADR5:
	case REG_EADR6:
	case REG_EADR7:
	case REG_RXFLUSH:
	case REG_ORDER:
	case REG_TXMCR:
	case REG_ACKTMOUT:
	case REG_ESLOTG1:
	case REG_SYMTICKL:
	case REG_SYMTICKH:
	case REG_PACON0:
	case REG_PACON1:
	case REG_PACON2:
	case REG_TXBCON0:
	case REG_TXNCON:
	case REG_TXG1CON:
	case REG_TXG2CON:
	case REG_ESLOTG23:
	case REG_ESLOTG45:
	case REG_ESLOTG67:
	case REG_TXPEND:
	case REG_WAKECON:
	case REG_FROMOFFSET:
	case REG_TXBCON1:
	case REG_GATECLK:
	case REG_TXTIME:
	case REG_HSYMTMRL:
	case REG_HSYMTMRH:
	case REG_SOFTRST:
	case REG_SECCON0:
	case REG_SECCON1:
	case REG_TXSTBL:
	case REG_RXSR:
	case REG_INTCON:
	case REG_TRISGPIO:
	case REG_GPIO:
	case REG_RFCTL:
	case REG_SECCR2:
	case REG_SLPACK:
	case REG_BBREG0:
	case REG_BBREG1:
	case REG_BBREG2:
	case REG_BBREG3:
	case REG_BBREG4:
	case REG_BBREG6:
	case REG_CCAEDTH:
		return true;
	default:
		return false;
	}
}