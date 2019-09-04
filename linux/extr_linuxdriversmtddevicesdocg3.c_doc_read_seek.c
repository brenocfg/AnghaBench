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
struct docg3 {int dummy; } ;

/* Variables and functions */
 int DOC_ADDR_BLOCK_SHIFT ; 
 int DOC_ADDR_PAGE_MASK ; 
 int /*<<< orphan*/  DOC_CMD_PROG_BLOCK_ADDR ; 
 int /*<<< orphan*/  DOC_CMD_READ_PLANE1 ; 
 int /*<<< orphan*/  DOC_CMD_READ_PLANE2 ; 
 int DOC_LAYOUT_PAGE_SIZE ; 
 int /*<<< orphan*/  DOC_SEQ_READ ; 
 int /*<<< orphan*/  DOC_SEQ_SET_PLANE1 ; 
 int /*<<< orphan*/  DOC_SEQ_SET_PLANE2 ; 
 int /*<<< orphan*/  doc_dbg (char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_set_extra_page_mode (struct docg3*) ; 
 int /*<<< orphan*/  doc_set_reliable_mode (struct docg3*) ; 
 int /*<<< orphan*/  doc_setup_addr_sector (struct docg3*,int) ; 

__attribute__((used)) static int doc_read_seek(struct docg3 *docg3, int block0, int block1, int page,
			 int wear, int ofs)
{
	int sector, ret = 0;

	doc_dbg("doc_seek(blocks=(%d,%d), page=%d, ofs=%d, wear=%d)\n",
		block0, block1, page, ofs, wear);

	if (!wear && (ofs < 2 * DOC_LAYOUT_PAGE_SIZE)) {
		doc_flash_sequence(docg3, DOC_SEQ_SET_PLANE1);
		doc_flash_command(docg3, DOC_CMD_READ_PLANE1);
		doc_delay(docg3, 2);
	} else {
		doc_flash_sequence(docg3, DOC_SEQ_SET_PLANE2);
		doc_flash_command(docg3, DOC_CMD_READ_PLANE2);
		doc_delay(docg3, 2);
	}

	doc_set_reliable_mode(docg3);
	if (wear)
		ret = doc_set_extra_page_mode(docg3);
	if (ret)
		goto out;

	doc_flash_sequence(docg3, DOC_SEQ_READ);
	sector = (block0 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	doc_flash_command(docg3, DOC_CMD_PROG_BLOCK_ADDR);
	doc_setup_addr_sector(docg3, sector);

	sector = (block1 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	doc_flash_command(docg3, DOC_CMD_PROG_BLOCK_ADDR);
	doc_setup_addr_sector(docg3, sector);
	doc_delay(docg3, 1);

out:
	return ret;
}