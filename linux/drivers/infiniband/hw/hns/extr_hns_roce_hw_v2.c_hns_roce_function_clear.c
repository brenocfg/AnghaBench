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
struct hns_roce_func_clear {int /*<<< orphan*/  func_done; } ;
struct hns_roce_dev {int is_reset; int /*<<< orphan*/  dev; } ;
struct hns_roce_cmq_desc {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC_CLEAR_RST_FUN_DONE_S ; 
 int /*<<< orphan*/  HNS_ROCE_OPC_FUNC_CLEAR ; 
 unsigned long HNS_ROCE_V2_FUNC_CLEAR_TIMEOUT_MSECS ; 
 scalar_t__ HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_FAIL_WAIT ; 
 scalar_t__ HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_INTERVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hns_roce_cmq_send (struct hns_roce_dev*,struct hns_roce_cmq_desc*,int) ; 
 int /*<<< orphan*/  hns_roce_cmq_setup_basic_desc (struct hns_roce_cmq_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ hns_roce_func_clr_chk_rst (struct hns_roce_dev*) ; 
 int /*<<< orphan*/  hns_roce_func_clr_rst_prc (struct hns_roce_dev*,int,int) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 scalar_t__ roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_roce_function_clear(struct hns_roce_dev *hr_dev)
{
	bool fclr_write_fail_flag = false;
	struct hns_roce_func_clear *resp;
	struct hns_roce_cmq_desc desc;
	unsigned long end;
	int ret = 0;

	if (hns_roce_func_clr_chk_rst(hr_dev))
		goto out;

	hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_FUNC_CLEAR, false);
	resp = (struct hns_roce_func_clear *)desc.data;

	ret = hns_roce_cmq_send(hr_dev, &desc, 1);
	if (ret) {
		fclr_write_fail_flag = true;
		dev_err(hr_dev->dev, "Func clear write failed, ret = %d.\n",
			 ret);
		goto out;
	}

	msleep(HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_INTERVAL);
	end = HNS_ROCE_V2_FUNC_CLEAR_TIMEOUT_MSECS;
	while (end) {
		if (hns_roce_func_clr_chk_rst(hr_dev))
			goto out;
		msleep(HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_FAIL_WAIT);
		end -= HNS_ROCE_V2_READ_FUNC_CLEAR_FLAG_FAIL_WAIT;

		hns_roce_cmq_setup_basic_desc(&desc, HNS_ROCE_OPC_FUNC_CLEAR,
					      true);

		ret = hns_roce_cmq_send(hr_dev, &desc, 1);
		if (ret)
			continue;

		if (roce_get_bit(resp->func_done, FUNC_CLEAR_RST_FUN_DONE_S)) {
			hr_dev->is_reset = true;
			return;
		}
	}

out:
	dev_err(hr_dev->dev, "Func clear fail.\n");
	hns_roce_func_clr_rst_prc(hr_dev, ret, fclr_write_fail_flag);
}