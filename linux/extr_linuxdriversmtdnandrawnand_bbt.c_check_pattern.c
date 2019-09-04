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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_bbt_descr {int options; int offs; int /*<<< orphan*/  len; int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int NAND_BBT_NO_OOB ; 
 int check_pattern_no_oob (int /*<<< orphan*/ *,struct nand_bbt_descr*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_pattern(uint8_t *buf, int len, int paglen, struct nand_bbt_descr *td)
{
	if (td->options & NAND_BBT_NO_OOB)
		return check_pattern_no_oob(buf, td);

	/* Compare the pattern */
	if (memcmp(buf + paglen + td->offs, td->pattern, td->len))
		return -1;

	return 0;
}