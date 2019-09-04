#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int erase_timeout; unsigned int erase_offset; int /*<<< orphan*/  au; } ;
struct TYPE_5__ {scalar_t__ sda_spec3; } ;
struct TYPE_4__ {int cmdclass; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_3__ ssr; int /*<<< orphan*/ * raw_ssr; TYPE_2__ scr; TYPE_1__ csd; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CCC_APP_SPEC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int UNSTUFF_BITS (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_app_sd_status (struct mmc_card*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sd_au_size ; 

__attribute__((used)) static int mmc_read_ssr(struct mmc_card *card)
{
	unsigned int au, es, et, eo;
	__be32 *raw_ssr;
	int i;

	if (!(card->csd.cmdclass & CCC_APP_SPEC)) {
		pr_warn("%s: card lacks mandatory SD Status function\n",
			mmc_hostname(card->host));
		return 0;
	}

	raw_ssr = kmalloc(sizeof(card->raw_ssr), GFP_KERNEL);
	if (!raw_ssr)
		return -ENOMEM;

	if (mmc_app_sd_status(card, raw_ssr)) {
		pr_warn("%s: problem reading SD Status register\n",
			mmc_hostname(card->host));
		kfree(raw_ssr);
		return 0;
	}

	for (i = 0; i < 16; i++)
		card->raw_ssr[i] = be32_to_cpu(raw_ssr[i]);

	kfree(raw_ssr);

	/*
	 * UNSTUFF_BITS only works with four u32s so we have to offset the
	 * bitfield positions accordingly.
	 */
	au = UNSTUFF_BITS(card->raw_ssr, 428 - 384, 4);
	if (au) {
		if (au <= 9 || card->scr.sda_spec3) {
			card->ssr.au = sd_au_size[au];
			es = UNSTUFF_BITS(card->raw_ssr, 408 - 384, 16);
			et = UNSTUFF_BITS(card->raw_ssr, 402 - 384, 6);
			if (es && et) {
				eo = UNSTUFF_BITS(card->raw_ssr, 400 - 384, 2);
				card->ssr.erase_timeout = (et * 1000) / es;
				card->ssr.erase_offset = eo * 1000;
			}
		} else {
			pr_warn("%s: SD Status: Invalid Allocation Unit size\n",
				mmc_hostname(card->host));
		}
	}

	return 0;
}