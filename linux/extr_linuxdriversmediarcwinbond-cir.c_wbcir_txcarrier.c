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
struct wbcir_data {scalar_t__ txstate; int txcarrier; int /*<<< orphan*/  spinlock; scalar_t__ sbase; } ;
struct rc_dev {struct wbcir_data* priv; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  WBCIR_BANK_7 ; 
 scalar_t__ WBCIR_REG_SP3_IRTXMC ; 
 scalar_t__ WBCIR_TXSTATE_INACTIVE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wbcir_select_bank (struct wbcir_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wbcir_set_bits (scalar_t__,int,int) ; 

__attribute__((used)) static int
wbcir_txcarrier(struct rc_dev *dev, u32 carrier)
{
	struct wbcir_data *data = dev->priv;
	unsigned long flags;
	u8 val;
	u32 freq;

	freq = DIV_ROUND_CLOSEST(carrier, 1000);
	if (freq < 30 || freq > 60)
		return -EINVAL;

	switch (freq) {
	case 58:
	case 59:
	case 60:
		val = freq - 58;
		freq *= 1000;
		break;
	case 57:
		val = freq - 27;
		freq = 56900;
		break;
	default:
		val = freq - 27;
		freq *= 1000;
		break;
	}

	spin_lock_irqsave(&data->spinlock, flags);
	if (data->txstate != WBCIR_TXSTATE_INACTIVE) {
		spin_unlock_irqrestore(&data->spinlock, flags);
		return -EBUSY;
	}

	if (data->txcarrier != freq) {
		wbcir_select_bank(data, WBCIR_BANK_7);
		wbcir_set_bits(data->sbase + WBCIR_REG_SP3_IRTXMC, val, 0x1F);
		data->txcarrier = freq;
	}

	spin_unlock_irqrestore(&data->spinlock, flags);
	return 0;
}