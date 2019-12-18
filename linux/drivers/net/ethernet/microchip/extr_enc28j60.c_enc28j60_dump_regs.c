#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct enc28j60_net {int /*<<< orphan*/  lock; TYPE_1__* spi; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECON1 ; 
 int /*<<< orphan*/  ECON2 ; 
 int /*<<< orphan*/  EIE ; 
 int /*<<< orphan*/  EIR ; 
 int /*<<< orphan*/  EPKTCNT ; 
 int /*<<< orphan*/  EREVID ; 
 int /*<<< orphan*/  ERXFCON ; 
 int /*<<< orphan*/  ERXNDL ; 
 int /*<<< orphan*/  ERXRDPTL ; 
 int /*<<< orphan*/  ERXSTL ; 
 int /*<<< orphan*/  ERXWRPTL ; 
 int /*<<< orphan*/  ESTAT ; 
 int /*<<< orphan*/  ETXNDL ; 
 int /*<<< orphan*/  ETXSTL ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  MACLCON1 ; 
 int /*<<< orphan*/  MACLCON2 ; 
 int /*<<< orphan*/  MACON1 ; 
 int /*<<< orphan*/  MACON3 ; 
 int /*<<< orphan*/  MACON4 ; 
 int /*<<< orphan*/  MAMXFLL ; 
 int /*<<< orphan*/  MAPHSUP ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,struct device*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nolock_regb_read (struct enc28j60_net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nolock_regw_read (struct enc28j60_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc28j60_dump_regs(struct enc28j60_net *priv, const char *msg)
{
	struct device *dev = &priv->spi->dev;

	mutex_lock(&priv->lock);
	dev_printk(KERN_DEBUG, dev,
		   " %s\n"
		   "HwRevID: 0x%02x\n"
		   "Cntrl: ECON1 ECON2 ESTAT  EIR  EIE\n"
		   "       0x%02x  0x%02x  0x%02x  0x%02x  0x%02x\n"
		   "MAC  : MACON1 MACON3 MACON4\n"
		   "       0x%02x   0x%02x   0x%02x\n"
		   "Rx   : ERXST  ERXND  ERXWRPT ERXRDPT ERXFCON EPKTCNT MAMXFL\n"
		   "       0x%04x 0x%04x 0x%04x  0x%04x  "
		   "0x%02x    0x%02x    0x%04x\n"
		   "Tx   : ETXST  ETXND  MACLCON1 MACLCON2 MAPHSUP\n"
		   "       0x%04x 0x%04x 0x%02x     0x%02x     0x%02x\n",
		   msg, nolock_regb_read(priv, EREVID),
		   nolock_regb_read(priv, ECON1), nolock_regb_read(priv, ECON2),
		   nolock_regb_read(priv, ESTAT), nolock_regb_read(priv, EIR),
		   nolock_regb_read(priv, EIE), nolock_regb_read(priv, MACON1),
		   nolock_regb_read(priv, MACON3), nolock_regb_read(priv, MACON4),
		   nolock_regw_read(priv, ERXSTL), nolock_regw_read(priv, ERXNDL),
		   nolock_regw_read(priv, ERXWRPTL),
		   nolock_regw_read(priv, ERXRDPTL),
		   nolock_regb_read(priv, ERXFCON),
		   nolock_regb_read(priv, EPKTCNT),
		   nolock_regw_read(priv, MAMXFLL), nolock_regw_read(priv, ETXSTL),
		   nolock_regw_read(priv, ETXNDL),
		   nolock_regb_read(priv, MACLCON1),
		   nolock_regb_read(priv, MACLCON2),
		   nolock_regb_read(priv, MAPHSUP));
	mutex_unlock(&priv->lock);
}