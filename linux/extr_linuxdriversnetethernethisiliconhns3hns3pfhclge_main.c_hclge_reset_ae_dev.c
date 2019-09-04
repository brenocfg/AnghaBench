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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hnae3_ae_dev {struct pci_dev* pdev; struct hclge_dev* priv; } ;
struct hclge_dev {int /*<<< orphan*/  vlan_table; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGE_DRIVER_NAME ; 
 int /*<<< orphan*/  HCLGE_STATE_DOWN ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MAX ; 
 int /*<<< orphan*/  HCLGE_TSO_MSS_MIN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int hclge_cmd_init (struct hclge_dev*) ; 
 int hclge_config_tso (struct hclge_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hclge_configure (struct hclge_dev*) ; 
 int hclge_get_cap (struct hclge_dev*) ; 
 int hclge_init_vlan_config (struct hclge_dev*) ; 
 int hclge_mac_init (struct hclge_dev*) ; 
 int hclge_map_tqp (struct hclge_dev*) ; 
 int hclge_rss_init_hw (struct hclge_dev*) ; 
 int /*<<< orphan*/  hclge_stats_clear (struct hclge_dev*) ; 
 int hclge_tm_init_hw (struct hclge_dev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_reset_ae_dev(struct hnae3_ae_dev *ae_dev)
{
	struct hclge_dev *hdev = ae_dev->priv;
	struct pci_dev *pdev = ae_dev->pdev;
	int ret;

	set_bit(HCLGE_STATE_DOWN, &hdev->state);

	hclge_stats_clear(hdev);
	memset(hdev->vlan_table, 0, sizeof(hdev->vlan_table));

	ret = hclge_cmd_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Cmd queue init failed\n");
		return ret;
	}

	ret = hclge_get_cap(hdev);
	if (ret) {
		dev_err(&pdev->dev, "get hw capability error, ret = %d.\n",
			ret);
		return ret;
	}

	ret = hclge_configure(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Configure dev error, ret = %d.\n", ret);
		return ret;
	}

	ret = hclge_map_tqp(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Map tqp error, ret = %d.\n", ret);
		return ret;
	}

	ret = hclge_mac_init(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Mac init error, ret = %d\n", ret);
		return ret;
	}

	ret = hclge_config_tso(hdev, HCLGE_TSO_MSS_MIN, HCLGE_TSO_MSS_MAX);
	if (ret) {
		dev_err(&pdev->dev, "Enable tso fail, ret =%d\n", ret);
		return ret;
	}

	ret = hclge_init_vlan_config(hdev);
	if (ret) {
		dev_err(&pdev->dev, "VLAN init fail, ret =%d\n", ret);
		return ret;
	}

	ret = hclge_tm_init_hw(hdev);
	if (ret) {
		dev_err(&pdev->dev, "tm init hw fail, ret =%d\n", ret);
		return ret;
	}

	ret = hclge_rss_init_hw(hdev);
	if (ret) {
		dev_err(&pdev->dev, "Rss init fail, ret =%d\n", ret);
		return ret;
	}

	dev_info(&pdev->dev, "Reset done, %s driver initialization finished.\n",
		 HCLGE_DRIVER_NAME);

	return 0;
}