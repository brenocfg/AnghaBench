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
struct sk_buff {int dummy; } ;
struct s3fwrn5_fw_info {int /*<<< orphan*/  completion; struct sk_buff* rsp; } ;
struct s3fwrn5_info {struct s3fwrn5_fw_info fw_info; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct sk_buff*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct s3fwrn5_info* nci_get_drvdata (struct nci_dev*) ; 

int s3fwrn5_fw_recv_frame(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct s3fwrn5_info *info = nci_get_drvdata(ndev);
	struct s3fwrn5_fw_info *fw_info = &info->fw_info;

	BUG_ON(fw_info->rsp);

	fw_info->rsp = skb;

	complete(&fw_info->completion);

	return 0;
}