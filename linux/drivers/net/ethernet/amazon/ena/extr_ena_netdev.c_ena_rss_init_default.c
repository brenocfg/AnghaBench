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
typedef  int /*<<< orphan*/  u32 ;
struct ena_com_dev {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  num_queues; TYPE_1__* pdev; struct ena_com_dev* ena_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_CRC32 ; 
 int /*<<< orphan*/  ENA_HASH_KEY_SIZE ; 
 int /*<<< orphan*/  ENA_IO_RXQ_IDX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_RX_RSS_TABLE_LOG_SIZE ; 
 int ENA_RX_RSS_TABLE_SIZE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int ena_com_fill_hash_function (struct ena_com_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ena_com_indirect_table_fill_entry (struct ena_com_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_rss_destroy (struct ena_com_dev*) ; 
 int ena_com_rss_init (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int ena_com_set_default_hash_ctrl (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ena_rss_init_default(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev = adapter->ena_dev;
	struct device *dev = &adapter->pdev->dev;
	int rc, i;
	u32 val;

	rc = ena_com_rss_init(ena_dev, ENA_RX_RSS_TABLE_LOG_SIZE);
	if (unlikely(rc)) {
		dev_err(dev, "Cannot init indirect table\n");
		goto err_rss_init;
	}

	for (i = 0; i < ENA_RX_RSS_TABLE_SIZE; i++) {
		val = ethtool_rxfh_indir_default(i, adapter->num_queues);
		rc = ena_com_indirect_table_fill_entry(ena_dev, i,
						       ENA_IO_RXQ_IDX(val));
		if (unlikely(rc && (rc != -EOPNOTSUPP))) {
			dev_err(dev, "Cannot fill indirect table\n");
			goto err_fill_indir;
		}
	}

	rc = ena_com_fill_hash_function(ena_dev, ENA_ADMIN_CRC32, NULL,
					ENA_HASH_KEY_SIZE, 0xFFFFFFFF);
	if (unlikely(rc && (rc != -EOPNOTSUPP))) {
		dev_err(dev, "Cannot fill hash function\n");
		goto err_fill_indir;
	}

	rc = ena_com_set_default_hash_ctrl(ena_dev);
	if (unlikely(rc && (rc != -EOPNOTSUPP))) {
		dev_err(dev, "Cannot fill hash control\n");
		goto err_fill_indir;
	}

	return 0;

err_fill_indir:
	ena_com_rss_destroy(ena_dev);
err_rss_init:

	return rc;
}