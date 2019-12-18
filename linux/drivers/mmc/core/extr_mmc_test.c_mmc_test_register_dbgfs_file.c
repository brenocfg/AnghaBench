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
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int S_IRUGO ; 
 int S_IWUSR ; 
 int __mmc_test_register_dbgfs_file (struct mmc_card*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_test_fops_test ; 
 int /*<<< orphan*/  mmc_test_lock ; 
 int /*<<< orphan*/  mtf_testlist_fops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mmc_test_register_dbgfs_file(struct mmc_card *card)
{
	int ret;

	mutex_lock(&mmc_test_lock);

	ret = __mmc_test_register_dbgfs_file(card, "test", S_IWUSR | S_IRUGO,
		&mmc_test_fops_test);
	if (ret)
		goto err;

	ret = __mmc_test_register_dbgfs_file(card, "testlist", S_IRUGO,
		&mtf_testlist_fops);
	if (ret)
		goto err;

err:
	mutex_unlock(&mmc_test_lock);

	return ret;
}