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
struct nand_chip {int /*<<< orphan*/  oob_poi; } ;
struct mtd_info {int dummy; } ;
struct docg4_priv {int oob_page; int /*<<< orphan*/  oob_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct docg4_priv* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static int docg4_write_oob(struct mtd_info *mtd, struct nand_chip *nand,
			   int page)
{
	/*
	 * Writing oob-only is not really supported, because MLC nand must write
	 * oob bytes at the same time as page data.  Nonetheless, we save the
	 * oob buffer contents here, and then write it along with the page data
	 * if the same page is subsequently written.  This allows user space
	 * utilities that write the oob data prior to the page data to work
	 * (e.g., nandwrite).  The disdvantage is that, if the intention was to
	 * write oob only, the operation is quietly ignored.  Also, oob can get
	 * corrupted if two concurrent processes are running nandwrite.
	 */

	/* note that bytes 7..14 are hw generated hamming/ecc and overwritten */
	struct docg4_priv *doc = nand_get_controller_data(nand);
	doc->oob_page = page;
	memcpy(doc->oob_buf, nand->oob_poi, 16);
	return 0;
}