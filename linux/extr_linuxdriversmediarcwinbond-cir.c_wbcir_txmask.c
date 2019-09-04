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
typedef  int u32 ;
struct wbcir_data {scalar_t__ txstate; int txmask; int /*<<< orphan*/  spinlock; scalar_t__ ebase; } ;
struct rc_dev {struct wbcir_data* priv; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ WBCIR_REG_ECEIR_CTS ; 
 scalar_t__ WBCIR_TXSTATE_INACTIVE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 

__attribute__((used)) static int
wbcir_txmask(struct rc_dev *dev, u32 mask)
{
	struct wbcir_data *data = dev->priv;
	unsigned long flags;
	u8 val;

	/* return the number of transmitters */
	if (mask > 15)
		return 4;

	/* Four outputs, only one output can be enabled at a time */
	switch (mask) {
	case 0x1:
		val = 0x0;
		break;
	case 0x2:
		val = 0x1;
		break;
	case 0x4:
		val = 0x2;
		break;
	case 0x8:
		val = 0x3;
		break;
	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&data->spinlock, flags);
	if (data->txstate != WBCIR_TXSTATE_INACTIVE) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		return -EBUSY;
	}

	if (data->txmask != mask) {
		wbcir_set_bits(data->ebase + WBCIR_REG_ECEIR_CTS, val, 0x0c);
		data->txmask = mask;
	}

	spin_unlock_irqrestore(&data->spinlock, flags);
	return 0;
}