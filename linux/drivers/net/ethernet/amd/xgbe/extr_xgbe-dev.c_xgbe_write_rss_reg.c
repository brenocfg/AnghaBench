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
struct xgbe_prv_data {int /*<<< orphan*/  rss_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDRT ; 
 int /*<<< orphan*/  CT ; 
 int EBUSY ; 
 int /*<<< orphan*/  MAC_RSSAR ; 
 int /*<<< orphan*/  MAC_RSSDR ; 
 int /*<<< orphan*/  OB ; 
 int /*<<< orphan*/  RSSIA ; 
 scalar_t__ XGMAC_IOREAD_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int xgbe_write_rss_reg(struct xgbe_prv_data *pdata, unsigned int type,
			      unsigned int index, unsigned int val)
{
	unsigned int wait;
	int ret = 0;

	mutex_lock(&pdata->rss_mutex);

	if (XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB)) {
		ret = -EBUSY;
		goto unlock;
	}

	XGMAC_IOWRITE(pdata, MAC_RSSDR, val);

	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, RSSIA, index);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, ADDRT, type);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, CT, 0);
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSAR, OB, 1);

	wait = 1000;
	while (wait--) {
		if (!XGMAC_IOREAD_BITS(pdata, MAC_RSSAR, OB))
			goto unlock;

		usleep_range(1000, 1500);
	}

	ret = -EBUSY;

unlock:
	mutex_unlock(&pdata->rss_mutex);

	return ret;
}