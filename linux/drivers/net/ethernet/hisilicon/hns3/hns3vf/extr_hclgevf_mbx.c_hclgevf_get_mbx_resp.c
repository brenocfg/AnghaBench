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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct hclgevf_mbx_resp_status {int origin_mbx_msg; int resp_status; int /*<<< orphan*/ * additional_info; int /*<<< orphan*/  received_resp; } ;
struct hclgevf_dev {TYPE_1__* pdev; struct hclgevf_mbx_resp_status mbx_resp; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int HCLGEVF_MAX_TRY_TIMES ; 
 int HCLGEVF_SLEEP_USECOND ; 
 int /*<<< orphan*/  HCLGEVF_STATE_CMD_DISABLE ; 
 scalar_t__ HCLGE_MBX_MAX_RESP_DATA_SIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  hclgevf_reset_mbx_resp_status (struct hclgevf_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hclgevf_get_mbx_resp(struct hclgevf_dev *hdev, u16 code0, u16 code1,
				u8 *resp_data, u16 resp_len)
{
#define HCLGEVF_MAX_TRY_TIMES	500
#define HCLGEVF_SLEEP_USECOND	1000
	struct hclgevf_mbx_resp_status *mbx_resp;
	u16 r_code0, r_code1;
	int i = 0;

	if (resp_len > HCLGE_MBX_MAX_RESP_DATA_SIZE) {
		dev_err(&hdev->pdev->dev,
			"VF mbx response len(=%d) exceeds maximum(=%d)\n",
			resp_len,
			HCLGE_MBX_MAX_RESP_DATA_SIZE);
		return -EINVAL;
	}

	while ((!hdev->mbx_resp.received_resp) && (i < HCLGEVF_MAX_TRY_TIMES)) {
		if (test_bit(HCLGEVF_STATE_CMD_DISABLE, &hdev->state))
			return -EIO;

		usleep_range(HCLGEVF_SLEEP_USECOND, HCLGEVF_SLEEP_USECOND * 2);
		i++;
	}

	if (i >= HCLGEVF_MAX_TRY_TIMES) {
		dev_err(&hdev->pdev->dev,
			"VF could not get mbx(%d,%d) resp(=%d) from PF in %d tries\n",
			code0, code1, hdev->mbx_resp.received_resp, i);
		return -EIO;
	}

	mbx_resp = &hdev->mbx_resp;
	r_code0 = (u16)(mbx_resp->origin_mbx_msg >> 16);
	r_code1 = (u16)(mbx_resp->origin_mbx_msg & 0xff);

	if (mbx_resp->resp_status)
		return mbx_resp->resp_status;

	if (resp_data)
		memcpy(resp_data, &mbx_resp->additional_info[0], resp_len);

	hclgevf_reset_mbx_resp_status(hdev);

	if (!(r_code0 == code0 && r_code1 == code1 && !mbx_resp->resp_status)) {
		dev_err(&hdev->pdev->dev,
			"VF could not match resp code(code0=%d,code1=%d), %d\n",
			code0, code1, mbx_resp->resp_status);
		dev_err(&hdev->pdev->dev,
			"VF could not match resp r_code(r_code0=%d,r_code1=%d)\n",
			r_code0, r_code1);
		return -EIO;
	}

	return 0;
}