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
struct nand_onfi_vendor_micron {int /*<<< orphan*/  read_retry_options; } ;
struct nand_chip {int /*<<< orphan*/  setup_read_retry; int /*<<< orphan*/  read_retries; struct nand_parameters parameters; } ;
struct TYPE_2__ {scalar_t__ vendor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ONFI_FEATURE_ADDR_READ_RETRY ; 
 int /*<<< orphan*/  ONFI_FEATURE_ON_DIE_ECC ; 
 int /*<<< orphan*/  micron_nand_setup_read_retry ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int micron_nand_onfi_init(struct nand_chip *chip)
{
	struct nand_parameters *p = &chip->parameters;

	if (p->onfi) {
		struct nand_onfi_vendor_micron *micron = (void *)p->onfi->vendor;

		chip->read_retries = micron->read_retry_options;
		chip->setup_read_retry = micron_nand_setup_read_retry;
	}

	if (p->supports_set_get_features) {
		set_bit(ONFI_FEATURE_ADDR_READ_RETRY, p->set_feature_list);
		set_bit(ONFI_FEATURE_ON_DIE_ECC, p->set_feature_list);
		set_bit(ONFI_FEATURE_ADDR_READ_RETRY, p->get_feature_list);
		set_bit(ONFI_FEATURE_ON_DIE_ECC, p->get_feature_list);
	}

	return 0;
}