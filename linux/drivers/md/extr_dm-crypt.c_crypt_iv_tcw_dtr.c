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
struct iv_tcw_private {int /*<<< orphan*/ * crc32_tfm; int /*<<< orphan*/ * whitening; int /*<<< orphan*/ * iv_seed; } ;
struct TYPE_2__ {struct iv_tcw_private tcw; } ;
struct crypt_config {TYPE_1__ iv_gen_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_free_shash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kzfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void crypt_iv_tcw_dtr(struct crypt_config *cc)
{
	struct iv_tcw_private *tcw = &cc->iv_gen_private.tcw;

	kzfree(tcw->iv_seed);
	tcw->iv_seed = NULL;
	kzfree(tcw->whitening);
	tcw->whitening = NULL;

	if (tcw->crc32_tfm && !IS_ERR(tcw->crc32_tfm))
		crypto_free_shash(tcw->crc32_tfm);
	tcw->crc32_tfm = NULL;
}