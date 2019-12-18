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
struct hclge_pkt_buf_alloc {int dummy; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hclge_common_thrd_config (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_common_wl_config (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_rx_buffer_calc (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_rx_priv_buf_alloc (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_rx_priv_wl_config (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_tx_buffer_alloc (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 int hclge_tx_buffer_calc (struct hclge_dev*,struct hclge_pkt_buf_alloc*) ; 
 scalar_t__ hnae3_dev_dcb_supported (struct hclge_dev*) ; 
 int /*<<< orphan*/  kfree (struct hclge_pkt_buf_alloc*) ; 
 struct hclge_pkt_buf_alloc* kzalloc (int,int /*<<< orphan*/ ) ; 

int hclge_buffer_alloc(struct hclge_dev *hdev)
{
	struct hclge_pkt_buf_alloc *pkt_buf;
	int ret;

	pkt_buf = kzalloc(sizeof(*pkt_buf), GFP_KERNEL);
	if (!pkt_buf)
		return -ENOMEM;

	ret = hclge_tx_buffer_calc(hdev, pkt_buf);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"could not calc tx buffer size for all TCs %d\n", ret);
		goto out;
	}

	ret = hclge_tx_buffer_alloc(hdev, pkt_buf);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"could not alloc tx buffers %d\n", ret);
		goto out;
	}

	ret = hclge_rx_buffer_calc(hdev, pkt_buf);
	if (ret) {
		dev_err(&hdev->pdev->dev,
			"could not calc rx priv buffer size for all TCs %d\n",
			ret);
		goto out;
	}

	ret = hclge_rx_priv_buf_alloc(hdev, pkt_buf);
	if (ret) {
		dev_err(&hdev->pdev->dev, "could not alloc rx priv buffer %d\n",
			ret);
		goto out;
	}

	if (hnae3_dev_dcb_supported(hdev)) {
		ret = hclge_rx_priv_wl_config(hdev, pkt_buf);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"could not configure rx private waterline %d\n",
				ret);
			goto out;
		}

		ret = hclge_common_thrd_config(hdev, pkt_buf);
		if (ret) {
			dev_err(&hdev->pdev->dev,
				"could not configure common threshold %d\n",
				ret);
			goto out;
		}
	}

	ret = hclge_common_wl_config(hdev, pkt_buf);
	if (ret)
		dev_err(&hdev->pdev->dev,
			"could not configure common waterline %d\n", ret);

out:
	kfree(pkt_buf);
	return ret;
}