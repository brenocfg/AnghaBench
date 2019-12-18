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
struct netdev_private {scalar_t__ PHYType; int duplexmode; int line_speed; int crvalue; int /*<<< orphan*/ * phys; scalar_t__ mem; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AhdocPHY ; 
 int CR_R_FD ; 
 int CR_R_PS10 ; 
 int CR_W_FD ; 
 int CR_W_PS10 ; 
 int CR_W_PS1000 ; 
 unsigned int DPLX_DET_FULL ; 
 unsigned int DPLX_FULL ; 
 int /*<<< orphan*/  DiagnosticReg ; 
 unsigned int FULLMODE ; 
 unsigned int Full_Duplex ; 
 unsigned int LXT1000_1000M ; 
 unsigned int LXT1000_100M ; 
 unsigned int LXT1000_Full ; 
 scalar_t__ LevelOnePHY ; 
 int /*<<< orphan*/  MIIRegister18 ; 
 scalar_t__ MarvellPHY ; 
 scalar_t__ Myson981 ; 
 scalar_t__ MysonPHY ; 
 unsigned int SPD_DET_100 ; 
 unsigned int SPEED100 ; 
 scalar_t__ SeeqPHY ; 
 int /*<<< orphan*/  SpecificReg ; 
 unsigned int SpeedMask ; 
 unsigned int Speed_100 ; 
 unsigned int Speed_1000M ; 
 unsigned int Speed_100M ; 
 int /*<<< orphan*/  StatusRegister ; 
 scalar_t__ TCRRCR ; 
 int ioread32 (scalar_t__) ; 
 unsigned int mdio_read (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netdev_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void getlinktype(struct net_device *dev)
{
	struct netdev_private *np = netdev_priv(dev);

	if (np->PHYType == MysonPHY) {	/* 3-in-1 case */
		if (ioread32(np->mem + TCRRCR) & CR_R_FD)
			np->duplexmode = 2;	/* full duplex */
		else
			np->duplexmode = 1;	/* half duplex */
		if (ioread32(np->mem + TCRRCR) & CR_R_PS10)
			np->line_speed = 1;	/* 10M */
		else
			np->line_speed = 2;	/* 100M */
	} else {
		if (np->PHYType == SeeqPHY) {	/* this PHY is SEEQ 80225 */
			unsigned int data;

			data = mdio_read(dev, np->phys[0], MIIRegister18);
			if (data & SPD_DET_100)
				np->line_speed = 2;	/* 100M */
			else
				np->line_speed = 1;	/* 10M */
			if (data & DPLX_DET_FULL)
				np->duplexmode = 2;	/* full duplex mode */
			else
				np->duplexmode = 1;	/* half duplex mode */
		} else if (np->PHYType == AhdocPHY) {
			unsigned int data;

			data = mdio_read(dev, np->phys[0], DiagnosticReg);
			if (data & Speed_100)
				np->line_speed = 2;	/* 100M */
			else
				np->line_speed = 1;	/* 10M */
			if (data & DPLX_FULL)
				np->duplexmode = 2;	/* full duplex mode */
			else
				np->duplexmode = 1;	/* half duplex mode */
		}
/* 89/6/13 add, (begin) */
		else if (np->PHYType == MarvellPHY) {
			unsigned int data;

			data = mdio_read(dev, np->phys[0], SpecificReg);
			if (data & Full_Duplex)
				np->duplexmode = 2;	/* full duplex mode */
			else
				np->duplexmode = 1;	/* half duplex mode */
			data &= SpeedMask;
			if (data == Speed_1000M)
				np->line_speed = 3;	/* 1000M */
			else if (data == Speed_100M)
				np->line_speed = 2;	/* 100M */
			else
				np->line_speed = 1;	/* 10M */
		}
/* 89/6/13 add, (end) */
/* 89/7/27 add, (begin) */
		else if (np->PHYType == Myson981) {
			unsigned int data;

			data = mdio_read(dev, np->phys[0], StatusRegister);

			if (data & SPEED100)
				np->line_speed = 2;
			else
				np->line_speed = 1;

			if (data & FULLMODE)
				np->duplexmode = 2;
			else
				np->duplexmode = 1;
		}
/* 89/7/27 add, (end) */
/* 89/12/29 add */
		else if (np->PHYType == LevelOnePHY) {
			unsigned int data;

			data = mdio_read(dev, np->phys[0], SpecificReg);
			if (data & LXT1000_Full)
				np->duplexmode = 2;	/* full duplex mode */
			else
				np->duplexmode = 1;	/* half duplex mode */
			data &= SpeedMask;
			if (data == LXT1000_1000M)
				np->line_speed = 3;	/* 1000M */
			else if (data == LXT1000_100M)
				np->line_speed = 2;	/* 100M */
			else
				np->line_speed = 1;	/* 10M */
		}
		np->crvalue &= (~CR_W_PS10) & (~CR_W_FD) & (~CR_W_PS1000);
		if (np->line_speed == 1)
			np->crvalue |= CR_W_PS10;
		else if (np->line_speed == 3)
			np->crvalue |= CR_W_PS1000;
		if (np->duplexmode == 2)
			np->crvalue |= CR_W_FD;
	}
}