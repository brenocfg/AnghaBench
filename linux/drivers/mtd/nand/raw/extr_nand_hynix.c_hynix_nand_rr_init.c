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
struct TYPE_2__ {int* data; } ;
struct nand_chip {TYPE_1__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int hynix_mlc_1xnm_rr_init (struct nand_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hynix_mlc_1xnm_rr_otps ; 
 int hynix_nand_has_valid_jedecid (struct nand_chip*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int hynix_nand_rr_init(struct nand_chip *chip)
{
	int i, ret = 0;
	bool valid_jedecid;

	valid_jedecid = hynix_nand_has_valid_jedecid(chip);

	/*
	 * We only support read-retry for 1xnm NANDs, and those NANDs all
	 * expose a valid JEDEC ID.
	 */
	if (valid_jedecid) {
		u8 nand_tech = chip->id.data[5] >> 4;

		/* 1xnm technology */
		if (nand_tech == 4) {
			for (i = 0; i < ARRAY_SIZE(hynix_mlc_1xnm_rr_otps);
			     i++) {
				/*
				 * FIXME: Hynix recommend to copy the
				 * read-retry OTP area into a normal page.
				 */
				ret = hynix_mlc_1xnm_rr_init(chip,
						hynix_mlc_1xnm_rr_otps);
				if (!ret)
					break;
			}
		}
	}

	if (ret)
		pr_warn("failed to initialize read-retry infrastructure");

	return 0;
}