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
 int /*<<< orphan*/  DOC_CMD_PROG_CYCLE1 ; 
 int /*<<< orphan*/  DOC_CMD_PROG_CYCLE3 ; 
 int /*<<< orphan*/  DOC_CMD_READ_PLANE1 ; 
 int /*<<< orphan*/  DOC_CMD_READ_PLANE2 ; 
 int DOC_LAYOUT_PAGE_SIZE ; 
 int /*<<< orphan*/  DOC_SEQ_PAGE_SETUP ; 
 int /*<<< orphan*/  DOC_SEQ_SET_PLANE1 ; 
 int /*<<< orphan*/  DOC_SEQ_SET_PLANE2 ; 
 int /*<<< orphan*/  doc_dbg (char*,int,int,int,int) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_set_reliable_mode (struct docg3*) ; 
 int /*<<< orphan*/  doc_setup_writeaddr_sector (struct docg3*,int,int) ; 
 int doc_wait_ready (struct docg3*) ; 

__attribute__((used)) static int doc_write_seek(struct docg3 *docg3, int block0, int block1, int page,
			 int ofs)
{
	int ret = 0, sector;

	doc_dbg("doc_write_seek(blocks=(%d,%d), page=%d, ofs=%d)\n",
		block0, block1, page, ofs);

	doc_set_reliable_mode(docg3);

	if (ofs < 2 * DOC_LAYOUT_PAGE_SIZE) {
		doc_flash_sequence(docg3, DOC_SEQ_SET_PLANE1);
		doc_flash_command(docg3, DOC_CMD_READ_PLANE1);
		doc_delay(docg3, 2);
	} else {
		doc_flash_sequence(docg3, DOC_SEQ_SET_PLANE2);
		doc_flash_command(docg3, DOC_CMD_READ_PLANE2);
		doc_delay(docg3, 2);
	}

	doc_flash_sequence(docg3, DOC_SEQ_PAGE_SETUP);
	doc_flash_command(docg3, DOC_CMD_PROG_CYCLE1);

	sector = (block0 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	doc_setup_writeaddr_sector(docg3, sector, ofs);

	doc_flash_command(docg3, DOC_CMD_PROG_CYCLE3);
	doc_delay(docg3, 2);
	ret = doc_wait_ready(docg3);
	if (ret)
		goto out;

	doc_flash_command(docg3, DOC_CMD_PROG_CYCLE1);
	sector = (block1 << DOC_ADDR_BLOCK_SHIFT) + (page & DOC_ADDR_PAGE_MASK);
	doc_setup_writeaddr_sector(docg3, sector, ofs);
	doc_delay(docg3, 1);

out:
	return ret;
}