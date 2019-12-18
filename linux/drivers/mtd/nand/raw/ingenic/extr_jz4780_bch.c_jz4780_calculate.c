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
typedef  int /*<<< orphan*/  u8 ;
struct ingenic_ecc_params {int /*<<< orphan*/  bytes; int /*<<< orphan*/  size; } ;
struct ingenic_ecc {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCH_BHINT_ENCF ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jz4780_bch_disable (struct ingenic_ecc*) ; 
 int /*<<< orphan*/  jz4780_bch_read_parity (struct ingenic_ecc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_bch_reset (struct ingenic_ecc*,struct ingenic_ecc_params*,int) ; 
 scalar_t__ jz4780_bch_wait_complete (struct ingenic_ecc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_bch_write_data (struct ingenic_ecc*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jz4780_calculate(struct ingenic_ecc *bch,
			    struct ingenic_ecc_params *params,
			    const u8 *buf, u8 *ecc_code)
{
	int ret = 0;

	mutex_lock(&bch->lock);

	jz4780_bch_reset(bch, params, true);
	jz4780_bch_write_data(bch, buf, params->size);

	if (jz4780_bch_wait_complete(bch, BCH_BHINT_ENCF, NULL)) {
		jz4780_bch_read_parity(bch, ecc_code, params->bytes);
	} else {
		dev_err(bch->dev, "timed out while calculating ECC\n");
		ret = -ETIMEDOUT;
	}

	jz4780_bch_disable(bch);
	mutex_unlock(&bch->lock);
	return ret;
}