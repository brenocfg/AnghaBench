#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {unsigned int num; TYPE_2__* card; int /*<<< orphan*/  max_blksize; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct mmc_card {int quirks; struct sdio_func** sdio_func; } ;
struct TYPE_3__ {int /*<<< orphan*/  blksize; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct TYPE_4__ {TYPE_1__ cis; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct sdio_func*) ; 
 int MMC_QUIRK_NONSTD_SDIO ; 
 int PTR_ERR (struct sdio_func*) ; 
 unsigned int SDIO_MAX_FUNCS ; 
 scalar_t__ WARN_ON (int) ; 
 struct sdio_func* sdio_alloc_func (struct mmc_card*) ; 
 int sdio_read_fbr (struct sdio_func*) ; 
 int sdio_read_func_cis (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_remove_func (struct sdio_func*) ; 

__attribute__((used)) static int sdio_init_func(struct mmc_card *card, unsigned int fn)
{
	int ret;
	struct sdio_func *func;

	if (WARN_ON(fn > SDIO_MAX_FUNCS))
		return -EINVAL;

	func = sdio_alloc_func(card);
	if (IS_ERR(func))
		return PTR_ERR(func);

	func->num = fn;

	if (!(card->quirks & MMC_QUIRK_NONSTD_SDIO)) {
		ret = sdio_read_fbr(func);
		if (ret)
			goto fail;

		ret = sdio_read_func_cis(func);
		if (ret)
			goto fail;
	} else {
		func->vendor = func->card->cis.vendor;
		func->device = func->card->cis.device;
		func->max_blksize = func->card->cis.blksize;
	}

	card->sdio_func[fn - 1] = func;

	return 0;

fail:
	/*
	 * It is okay to remove the function here even though we hold
	 * the host lock as we haven't registered the device yet.
	 */
	sdio_remove_func(func);
	return ret;
}