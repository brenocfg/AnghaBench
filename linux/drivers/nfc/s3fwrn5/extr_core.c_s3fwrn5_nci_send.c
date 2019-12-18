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
struct s3fwrn5_info {int /*<<< orphan*/  mutex; } ;
struct nci_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3FWRN5_MODE_NCI ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s3fwrn5_info* nci_get_drvdata (struct nci_dev*) ; 
 scalar_t__ s3fwrn5_get_mode (struct s3fwrn5_info*) ; 
 int s3fwrn5_write (struct s3fwrn5_info*,struct sk_buff*) ; 

__attribute__((used)) static int s3fwrn5_nci_send(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct s3fwrn5_info *info = nci_get_drvdata(ndev);
	int ret;

	mutex_lock(&info->mutex);

	if (s3fwrn5_get_mode(info) != S3FWRN5_MODE_NCI) {
		mutex_unlock(&info->mutex);
		return -EINVAL;
	}

	ret = s3fwrn5_write(info, skb);
	if (ret < 0)
		kfree_skb(skb);

	mutex_unlock(&info->mutex);
	return ret;
}