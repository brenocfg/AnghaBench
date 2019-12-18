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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct meson_ao_cec_g12a_device {int /*<<< orphan*/  regmap_cec; } ;
struct cec_msg {int len; int* msg; } ;
struct cec_adapter {struct meson_ao_cec_g12a_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CECB_CTRL ; 
 int CECB_CTRL_SEND ; 
 int CECB_CTRL_TYPE ; 
 unsigned int CECB_CTRL_TYPE_NEW ; 
 unsigned int CECB_CTRL_TYPE_NEXT ; 
 unsigned int CECB_CTRL_TYPE_RETRY ; 
 int /*<<< orphan*/  CECB_LOCK_BUF ; 
 int CECB_LOCK_BUF_EN ; 
 scalar_t__ CECB_TX_CNT ; 
 scalar_t__ CECB_TX_DATA00 ; 
#define  CEC_SIGNAL_FREE_TIME_NEW_INITIATOR 130 
#define  CEC_SIGNAL_FREE_TIME_NEXT_XFER 129 
#define  CEC_SIGNAL_FREE_TIME_RETRY 128 
 int EBUSY ; 
 int EIO ; 
 int FIELD_PREP (int,unsigned int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int meson_ao_cec_g12a_transmit(struct cec_adapter *adap, u8 attempts,
				 u32 signal_free_time, struct cec_msg *msg)
{
	struct meson_ao_cec_g12a_device *ao_cec = adap->priv;
	unsigned int type;
	int ret = 0;
	u32 val;
	int i;

	/* Check if RX is in progress */
	ret = regmap_read(ao_cec->regmap_cec, CECB_LOCK_BUF, &val);
	if (ret)
		return ret;
	if (val & CECB_LOCK_BUF_EN)
		return -EBUSY;

	/* Check if TX Busy */
	ret = regmap_read(ao_cec->regmap_cec, CECB_CTRL, &val);
	if (ret)
		return ret;
	if (val & CECB_CTRL_SEND)
		return -EBUSY;

	switch (signal_free_time) {
	case CEC_SIGNAL_FREE_TIME_RETRY:
		type = CECB_CTRL_TYPE_RETRY;
		break;
	case CEC_SIGNAL_FREE_TIME_NEXT_XFER:
		type = CECB_CTRL_TYPE_NEXT;
		break;
	case CEC_SIGNAL_FREE_TIME_NEW_INITIATOR:
	default:
		type = CECB_CTRL_TYPE_NEW;
		break;
	}

	for (i = 0; i < msg->len; i++)
		ret |= regmap_write(ao_cec->regmap_cec, CECB_TX_DATA00 + i,
				    msg->msg[i]);

	ret |= regmap_write(ao_cec->regmap_cec, CECB_TX_CNT, msg->len);
	if (ret)
		return -EIO;

	ret = regmap_update_bits(ao_cec->regmap_cec, CECB_CTRL,
				 CECB_CTRL_SEND |
				 CECB_CTRL_TYPE,
				 CECB_CTRL_SEND |
				 FIELD_PREP(CECB_CTRL_TYPE, type));

	return ret;
}