#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nci_dev {int dummy; } ;
struct fdp_nci_info {void (* data_pkt_counter_cb ) (struct nci_dev*) ;int /*<<< orphan*/  data_pkt_counter; TYPE_2__* phy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* i2c_dev; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct fdp_nci_info* nci_get_drvdata (struct nci_dev*) ; 

__attribute__((used)) static void fdp_nci_set_data_pkt_counter(struct nci_dev *ndev,
				  void (*cb)(struct nci_dev *ndev), int count)
{
	struct fdp_nci_info *info = nci_get_drvdata(ndev);
	struct device *dev = &info->phy->i2c_dev->dev;

	dev_dbg(dev, "NCI data pkt counter %d\n", count);
	atomic_set(&info->data_pkt_counter, count);
	info->data_pkt_counter_cb = cb;
}