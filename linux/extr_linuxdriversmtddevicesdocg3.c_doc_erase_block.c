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
 int /*<<< orphan*/  DOC_CMD_ERASECYCLE2 ; 
 int /*<<< orphan*/  DOC_CMD_PROG_BLOCK_ADDR ; 
 int /*<<< orphan*/  DOC_SEQ_ERASE ; 
 int EIO ; 
 int /*<<< orphan*/  doc_dbg (char*,int,int) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_err (char*,int,int) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_flash_sequence (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_reset_seq (struct docg3*) ; 
 int /*<<< orphan*/  doc_set_reliable_mode (struct docg3*) ; 
 int /*<<< orphan*/  doc_setup_addr_sector (struct docg3*,int) ; 
 int doc_write_erase_wait_status (struct docg3*) ; 
 scalar_t__ is_prot_seq_error (struct docg3*) ; 

__attribute__((used)) static int doc_erase_block(struct docg3 *docg3, int block0, int block1)
{
	int ret, sector;

	doc_dbg("doc_erase_block(blocks=(%d,%d))\n", block0, block1);
	ret = doc_reset_seq(docg3);
	if (ret)
		return -EIO;

	doc_set_reliable_mode(docg3);
	doc_flash_sequence(docg3, DOC_SEQ_ERASE);

	sector = block0 << DOC_ADDR_BLOCK_SHIFT;
	doc_flash_command(docg3, DOC_CMD_PROG_BLOCK_ADDR);
	doc_setup_addr_sector(docg3, sector);
	sector = block1 << DOC_ADDR_BLOCK_SHIFT;
	doc_flash_command(docg3, DOC_CMD_PROG_BLOCK_ADDR);
	doc_setup_addr_sector(docg3, sector);
	doc_delay(docg3, 1);

	doc_flash_command(docg3, DOC_CMD_ERASECYCLE2);
	doc_delay(docg3, 2);

	if (is_prot_seq_error(docg3)) {
		doc_err("Erase blocks %d,%d error\n", block0, block1);
		return -EIO;
	}

	return doc_write_erase_wait_status(docg3);
}