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
typedef  int u64 ;
typedef  int u32 ;
struct cnic_local {int ctx_blks; int cids_per_blk; TYPE_1__* ctx_arr; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct TYPE_2__ {int cid; int mapping; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct cnic_local*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 int /*<<< orphan*/  BNX2_CTX_HOST_PAGE_TBL_CTRL ; 
 int BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ ; 
 int /*<<< orphan*/  BNX2_CTX_HOST_PAGE_TBL_DATA0 ; 
 int BNX2_CTX_HOST_PAGE_TBL_DATA0_VALID ; 
 int /*<<< orphan*/  BNX2_CTX_HOST_PAGE_TBL_DATA1 ; 
 int /*<<< orphan*/  CNIC_PAGE_SIZE ; 
 int CNIC_RD (struct cnic_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNIC_WR (struct cnic_dev*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int cnic_setup_5709_context(struct cnic_dev *dev, int valid)
{
	struct cnic_local *cp = dev->cnic_priv;
	int ret = 0, i;
	u32 valid_bit = valid ? BNX2_CTX_HOST_PAGE_TBL_DATA0_VALID : 0;

	if (BNX2_CHIP(cp) != BNX2_CHIP_5709)
		return 0;

	for (i = 0; i < cp->ctx_blks; i++) {
		int j;
		u32 idx = cp->ctx_arr[i].cid / cp->cids_per_blk;
		u32 val;

		memset(cp->ctx_arr[i].ctx, 0, CNIC_PAGE_SIZE);

		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_DATA0,
			(cp->ctx_arr[i].mapping & 0xffffffff) | valid_bit);
		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_DATA1,
			(u64) cp->ctx_arr[i].mapping >> 32);
		CNIC_WR(dev, BNX2_CTX_HOST_PAGE_TBL_CTRL, idx |
			BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ);
		for (j = 0; j < 10; j++) {

			val = CNIC_RD(dev, BNX2_CTX_HOST_PAGE_TBL_CTRL);
			if (!(val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ))
				break;
			udelay(5);
		}
		if (val & BNX2_CTX_HOST_PAGE_TBL_CTRL_WRITE_REQ) {
			ret = -EBUSY;
			break;
		}
	}
	return ret;
}