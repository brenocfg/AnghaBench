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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int capacity; } ;
struct mmc_card {int /*<<< orphan*/  host; TYPE_1__ csd; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_can_ext_csd (struct mmc_card*) ; 
 int mmc_decode_ext_csd (struct mmc_card*,int /*<<< orphan*/ *) ; 
 int mmc_get_ext_csd (struct mmc_card*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmc_read_ext_csd(struct mmc_card *card)
{
	u8 *ext_csd;
	int err;

	if (!mmc_can_ext_csd(card))
		return 0;

	err = mmc_get_ext_csd(card, &ext_csd);
	if (err) {
		/* If the host or the card can't do the switch,
		 * fail more gracefully. */
		if ((err != -EINVAL)
		 && (err != -ENOSYS)
		 && (err != -EFAULT))
			return err;

		/*
		 * High capacity cards should have this "magic" size
		 * stored in their CSD.
		 */
		if (card->csd.capacity == (4096 * 512)) {
			pr_err("%s: unable to read EXT_CSD on a possible high capacity card. Card will be ignored.\n",
				mmc_hostname(card->host));
		} else {
			pr_warn("%s: unable to read EXT_CSD, performance might suffer\n",
				mmc_hostname(card->host));
			err = 0;
		}

		return err;
	}

	err = mmc_decode_ext_csd(card, ext_csd);
	kfree(ext_csd);
	return err;
}