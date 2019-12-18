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
struct nand_chip {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int denali_oob_xfer (struct nand_chip*,void*,int) ; 
 int denali_payload_xfer (struct nand_chip*,void*,int) ; 
 int nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int denali_read_raw(struct nand_chip *chip, void *buf, void *oob_buf,
			   int page)
{
	int ret;

	if (!buf && !oob_buf)
		return -EINVAL;

	ret = nand_read_page_op(chip, page, 0, NULL, 0);
	if (ret)
		return ret;

	if (buf) {
		ret = denali_payload_xfer(chip, buf, false);
		if (ret)
			return ret;
	}

	if (oob_buf) {
		ret = denali_oob_xfer(chip, oob_buf, false);
		if (ret)
			return ret;
	}

	return 0;
}