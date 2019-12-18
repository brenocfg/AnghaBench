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
typedef  int u8 ;
typedef  int u32 ;
struct ingenic_ecc_params {int /*<<< orphan*/  bytes; int /*<<< orphan*/  size; } ;
struct ingenic_ecc {int /*<<< orphan*/  lock; scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BCH_BHERR0 ; 
 int BCH_BHERR_INDEX_MASK ; 
 int BCH_BHERR_INDEX_SHIFT ; 
 int BCH_BHERR_MASK_MASK ; 
 int BCH_BHERR_MASK_SHIFT ; 
 int /*<<< orphan*/  BCH_BHINT_DECF ; 
 int BCH_BHINT_ERR ; 
 int BCH_BHINT_ERRC_MASK ; 
 int BCH_BHINT_ERRC_SHIFT ; 
 int BCH_BHINT_TERRC_MASK ; 
 int BCH_BHINT_TERRC_SHIFT ; 
 int BCH_BHINT_UNCOR ; 
 int EBADMSG ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jz4780_bch_disable (struct ingenic_ecc*) ; 
 int /*<<< orphan*/  jz4780_bch_reset (struct ingenic_ecc*,struct ingenic_ecc_params*,int) ; 
 int /*<<< orphan*/  jz4780_bch_wait_complete (struct ingenic_ecc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  jz4780_bch_write_data (struct ingenic_ecc*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int jz4780_correct(struct ingenic_ecc *bch,
			  struct ingenic_ecc_params *params,
			  u8 *buf, u8 *ecc_code)
{
	u32 reg, mask, index;
	int i, ret, count;

	mutex_lock(&bch->lock);

	jz4780_bch_reset(bch, params, false);
	jz4780_bch_write_data(bch, buf, params->size);
	jz4780_bch_write_data(bch, ecc_code, params->bytes);

	if (!jz4780_bch_wait_complete(bch, BCH_BHINT_DECF, &reg)) {
		dev_err(bch->dev, "timed out while correcting data\n");
		ret = -ETIMEDOUT;
		goto out;
	}

	if (reg & BCH_BHINT_UNCOR) {
		dev_warn(bch->dev, "uncorrectable ECC error\n");
		ret = -EBADMSG;
		goto out;
	}

	/* Correct any detected errors. */
	if (reg & BCH_BHINT_ERR) {
		count = (reg & BCH_BHINT_ERRC_MASK) >> BCH_BHINT_ERRC_SHIFT;
		ret = (reg & BCH_BHINT_TERRC_MASK) >> BCH_BHINT_TERRC_SHIFT;

		for (i = 0; i < count; i++) {
			reg = readl(bch->base + BCH_BHERR0 + (i * 4));
			mask = (reg & BCH_BHERR_MASK_MASK) >>
						BCH_BHERR_MASK_SHIFT;
			index = (reg & BCH_BHERR_INDEX_MASK) >>
						BCH_BHERR_INDEX_SHIFT;
			buf[(index * 2) + 0] ^= mask;
			buf[(index * 2) + 1] ^= mask >> 8;
		}
	} else {
		ret = 0;
	}

out:
	jz4780_bch_disable(bch);
	mutex_unlock(&bch->lock);
	return ret;
}