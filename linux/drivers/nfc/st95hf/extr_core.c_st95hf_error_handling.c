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
struct st95hf_context {int current_rf_tech; int /*<<< orphan*/  sendrcv_trflag; TYPE_1__* nfcdev; } ;
struct sk_buff {int* data; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
#define  NFC_DIGITAL_RF_TECH_106A 130 
#define  NFC_DIGITAL_RF_TECH_106B 129 
#define  NFC_DIGITAL_RF_TECH_ISO15693 128 
 int ST95HF_ERR_MASK ; 
 unsigned char ST95HF_NFCA_CRC_ERR_MASK ; 
 unsigned char ST95HF_NFCB_CRC_ERR_MASK ; 
 int ST95HF_TIMEOUT_ERROR ; 
 int /*<<< orphan*/  TRFLAG_NFCA_STD_FRAME_CRC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned char) ; 

__attribute__((used)) static int st95hf_error_handling(struct st95hf_context *stcontext,
				 struct sk_buff *skb_resp,
				 int res_len)
{
	int result = 0;
	unsigned char error_byte;
	struct device *dev = &stcontext->nfcdev->dev;

	/* First check ST95HF specific error */
	if (skb_resp->data[0] & ST95HF_ERR_MASK) {
		if (skb_resp->data[0] == ST95HF_TIMEOUT_ERROR)
			result = -ETIMEDOUT;
		else
			result = -EIO;
		return result;
	}

	/* Check for CRC err only if CRC is present in the tag response */
	switch (stcontext->current_rf_tech) {
	case NFC_DIGITAL_RF_TECH_106A:
		if (stcontext->sendrcv_trflag == TRFLAG_NFCA_STD_FRAME_CRC) {
			error_byte = skb_resp->data[res_len - 3];
			if (error_byte & ST95HF_NFCA_CRC_ERR_MASK) {
				/* CRC error occurred */
				dev_err(dev, "CRC error, byte received = 0x%x\n",
					error_byte);
				result = -EIO;
			}
		}
		break;
	case NFC_DIGITAL_RF_TECH_106B:
	case NFC_DIGITAL_RF_TECH_ISO15693:
		error_byte = skb_resp->data[res_len - 1];
		if (error_byte & ST95HF_NFCB_CRC_ERR_MASK) {
			/* CRC error occurred */
			dev_err(dev, "CRC error, byte received = 0x%x\n",
				error_byte);
			result = -EIO;
		}
		break;
	}

	return result;
}