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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  set_feature_list; int /*<<< orphan*/  supports_set_get_features; } ;
struct nand_chip {TYPE_1__ parameters; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  ONFI_FEATURE_ADDR_READ_RETRY ; 
 int ONFI_SUBFEATURE_PARAM_LEN ; 
 int nand_set_features (struct nand_chip*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macronix_nand_setup_read_retry(struct nand_chip *chip, int mode)
{
	u8 feature[ONFI_SUBFEATURE_PARAM_LEN];

	if (!chip->parameters.supports_set_get_features ||
	    !test_bit(ONFI_FEATURE_ADDR_READ_RETRY,
		      chip->parameters.set_feature_list))
		return -ENOTSUPP;

	feature[0] = mode;
	return nand_set_features(chip, ONFI_FEATURE_ADDR_READ_RETRY, feature);
}