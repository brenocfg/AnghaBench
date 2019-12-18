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
struct nand_parameters {int /*<<< orphan*/  get_feature_list; int /*<<< orphan*/  set_feature_list; scalar_t__ supports_set_get_features; TYPE_1__* onfi; } ;
struct nand_onfi_vendor_macronix {int reliability_func; } ;
struct nand_chip {int /*<<< orphan*/  setup_read_retry; int /*<<< orphan*/  read_retries; struct nand_parameters parameters; } ;
struct TYPE_2__ {scalar_t__ vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACRONIX_NUM_READ_RETRY_MODES ; 
 int MACRONIX_READ_RETRY_BIT ; 
 int /*<<< orphan*/  ONFI_FEATURE_ADDR_READ_RETRY ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  macronix_nand_setup_read_retry ; 

__attribute__((used)) static void macronix_nand_onfi_init(struct nand_chip *chip)
{
	struct nand_parameters *p = &chip->parameters;
	struct nand_onfi_vendor_macronix *mxic;

	if (!p->onfi)
		return;

	mxic = (struct nand_onfi_vendor_macronix *)p->onfi->vendor;
	if ((mxic->reliability_func & MACRONIX_READ_RETRY_BIT) == 0)
		return;

	chip->read_retries = MACRONIX_NUM_READ_RETRY_MODES;
	chip->setup_read_retry = macronix_nand_setup_read_retry;

	if (p->supports_set_get_features) {
		bitmap_set(p->set_feature_list,
			   ONFI_FEATURE_ADDR_READ_RETRY, 1);
		bitmap_set(p->get_feature_list,
			   ONFI_FEATURE_ADDR_READ_RETRY, 1);
	}
}