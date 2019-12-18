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
typedef  int u8 ;
struct tda998x_priv {int /*<<< orphan*/  wq_edid; scalar_t__ wq_edid_wait; int /*<<< orphan*/  cec_notify; int /*<<< orphan*/  detect_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CEC_INTSTATUS_HDMI ; 
 int /*<<< orphan*/  CEC_PHYS_ADDR_INVALID ; 
 int CEC_RXSHPDINT_HPD ; 
 int CEC_RXSHPDLEV_HPD ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int,int,int,int,int) ; 
 int INT_FLAGS_2_EDID_BLK_RD ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  REG_CEC_INTSTATUS ; 
 int /*<<< orphan*/  REG_CEC_RXSHPDINT ; 
 int /*<<< orphan*/  REG_CEC_RXSHPDLEV ; 
 int /*<<< orphan*/  REG_INT_FLAGS_0 ; 
 int /*<<< orphan*/  REG_INT_FLAGS_1 ; 
 int /*<<< orphan*/  REG_INT_FLAGS_2 ; 
 int /*<<< orphan*/  cec_notifier_set_phys_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cec_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 int reg_read (struct tda998x_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tda998x_edid_delay_start (struct tda998x_priv*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tda998x_irq_thread(int irq, void *data)
{
	struct tda998x_priv *priv = data;
	u8 sta, cec, lvl, flag0, flag1, flag2;
	bool handled = false;

	sta = cec_read(priv, REG_CEC_INTSTATUS);
	if (sta & CEC_INTSTATUS_HDMI) {
		cec = cec_read(priv, REG_CEC_RXSHPDINT);
		lvl = cec_read(priv, REG_CEC_RXSHPDLEV);
		flag0 = reg_read(priv, REG_INT_FLAGS_0);
		flag1 = reg_read(priv, REG_INT_FLAGS_1);
		flag2 = reg_read(priv, REG_INT_FLAGS_2);
		DRM_DEBUG_DRIVER(
			"tda irq sta %02x cec %02x lvl %02x f0 %02x f1 %02x f2 %02x\n",
			sta, cec, lvl, flag0, flag1, flag2);

		if (cec & CEC_RXSHPDINT_HPD) {
			if (lvl & CEC_RXSHPDLEV_HPD) {
				tda998x_edid_delay_start(priv);
			} else {
				schedule_work(&priv->detect_work);
				cec_notifier_set_phys_addr(priv->cec_notify,
						   CEC_PHYS_ADDR_INVALID);
			}

			handled = true;
		}

		if ((flag2 & INT_FLAGS_2_EDID_BLK_RD) && priv->wq_edid_wait) {
			priv->wq_edid_wait = 0;
			wake_up(&priv->wq_edid);
			handled = true;
		}
	}

	return IRQ_RETVAL(handled);
}