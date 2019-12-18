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
struct smsm_host {int /*<<< orphan*/  ipc_bit; int /*<<< orphan*/  ipc_offset; int /*<<< orphan*/  ipc_regmap; } ;
struct qcom_smsm {TYPE_1__* dev; struct smsm_host* hosts; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int smsm_parse_ipc(struct qcom_smsm *smsm, unsigned host_id)
{
	struct device_node *syscon;
	struct device_node *node = smsm->dev->of_node;
	struct smsm_host *host = &smsm->hosts[host_id];
	char key[16];
	int ret;

	snprintf(key, sizeof(key), "qcom,ipc-%d", host_id);
	syscon = of_parse_phandle(node, key, 0);
	if (!syscon)
		return 0;

	host->ipc_regmap = syscon_node_to_regmap(syscon);
	if (IS_ERR(host->ipc_regmap))
		return PTR_ERR(host->ipc_regmap);

	ret = of_property_read_u32_index(node, key, 1, &host->ipc_offset);
	if (ret < 0) {
		dev_err(smsm->dev, "no offset in %s\n", key);
		return -EINVAL;
	}

	ret = of_property_read_u32_index(node, key, 2, &host->ipc_bit);
	if (ret < 0) {
		dev_err(smsm->dev, "no bit in %s\n", key);
		return -EINVAL;
	}

	return 0;
}