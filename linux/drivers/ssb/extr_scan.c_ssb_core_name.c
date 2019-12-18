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
#define  SSB_DEV_80211 160 
#define  SSB_DEV_ADSL 159 
#define  SSB_DEV_ARM_1176 158 
#define  SSB_DEV_ARM_7TDMI 157 
#define  SSB_DEV_ARM_CM3 156 
#define  SSB_DEV_CHIPCOMMON 155 
#define  SSB_DEV_ETHERNET 154 
#define  SSB_DEV_ETHERNET_GBIT 153 
#define  SSB_DEV_EXTIF 152 
#define  SSB_DEV_ILINE100 151 
#define  SSB_DEV_ILINE20 150 
#define  SSB_DEV_INTERNAL_MEM 149 
#define  SSB_DEV_IPSEC 148 
#define  SSB_DEV_MEMC_SDRAM 147 
#define  SSB_DEV_MIMO_PHY 146 
#define  SSB_DEV_MINI_MACPHY 145 
#define  SSB_DEV_MIPS 144 
#define  SSB_DEV_MIPS_3302 143 
#define  SSB_DEV_PARA_ATA 142 
#define  SSB_DEV_PCI 141 
#define  SSB_DEV_PCIE 140 
#define  SSB_DEV_PCMCIA 139 
#define  SSB_DEV_ROBOSWITCH 138 
#define  SSB_DEV_SATA_XORDMA 137 
#define  SSB_DEV_SDIO_HOST 136 
#define  SSB_DEV_SDRAM 135 
#define  SSB_DEV_SRAM_CTRLR 134 
#define  SSB_DEV_USB11_DEV 133 
#define  SSB_DEV_USB11_HOST 132 
#define  SSB_DEV_USB11_HOSTDEV 131 
#define  SSB_DEV_USB20_DEV 130 
#define  SSB_DEV_USB20_HOST 129 
#define  SSB_DEV_V90 128 

const char *ssb_core_name(u16 coreid)
{
	switch (coreid) {
	case SSB_DEV_CHIPCOMMON:
		return "ChipCommon";
	case SSB_DEV_ILINE20:
		return "ILine 20";
	case SSB_DEV_SDRAM:
		return "SDRAM";
	case SSB_DEV_PCI:
		return "PCI";
	case SSB_DEV_MIPS:
		return "MIPS";
	case SSB_DEV_ETHERNET:
		return "Fast Ethernet";
	case SSB_DEV_V90:
		return "V90";
	case SSB_DEV_USB11_HOSTDEV:
		return "USB 1.1 Hostdev";
	case SSB_DEV_ADSL:
		return "ADSL";
	case SSB_DEV_ILINE100:
		return "ILine 100";
	case SSB_DEV_IPSEC:
		return "IPSEC";
	case SSB_DEV_PCMCIA:
		return "PCMCIA";
	case SSB_DEV_INTERNAL_MEM:
		return "Internal Memory";
	case SSB_DEV_MEMC_SDRAM:
		return "MEMC SDRAM";
	case SSB_DEV_EXTIF:
		return "EXTIF";
	case SSB_DEV_80211:
		return "IEEE 802.11";
	case SSB_DEV_MIPS_3302:
		return "MIPS 3302";
	case SSB_DEV_USB11_HOST:
		return "USB 1.1 Host";
	case SSB_DEV_USB11_DEV:
		return "USB 1.1 Device";
	case SSB_DEV_USB20_HOST:
		return "USB 2.0 Host";
	case SSB_DEV_USB20_DEV:
		return "USB 2.0 Device";
	case SSB_DEV_SDIO_HOST:
		return "SDIO Host";
	case SSB_DEV_ROBOSWITCH:
		return "Roboswitch";
	case SSB_DEV_PARA_ATA:
		return "PATA";
	case SSB_DEV_SATA_XORDMA:
		return "SATA XOR-DMA";
	case SSB_DEV_ETHERNET_GBIT:
		return "GBit Ethernet";
	case SSB_DEV_PCIE:
		return "PCI-E";
	case SSB_DEV_MIMO_PHY:
		return "MIMO PHY";
	case SSB_DEV_SRAM_CTRLR:
		return "SRAM Controller";
	case SSB_DEV_MINI_MACPHY:
		return "Mini MACPHY";
	case SSB_DEV_ARM_1176:
		return "ARM 1176";
	case SSB_DEV_ARM_7TDMI:
		return "ARM 7TDMI";
	case SSB_DEV_ARM_CM3:
		return "ARM Cortex M3";
	}
	return "UNKNOWN";
}