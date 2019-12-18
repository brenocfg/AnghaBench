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
struct docg3 {int /*<<< orphan*/  device_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOC_CMD_READ_ALL_PLANES ; 
 int /*<<< orphan*/  DOC_CMD_READ_FLASH ; 
 int /*<<< orphan*/  DOC_CMD_SET_ADDR_READ ; 
 int /*<<< orphan*/  DOC_DATAEND ; 
 int DOC_LAYOUT_PAGE_OOB_SIZE ; 
 int DOC_LAYOUT_PAGE_SIZE ; 
 int DOC_LAYOUT_WEAR_OFFSET ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  doc_dbg (char*,int,int,int,int) ; 
 int /*<<< orphan*/  doc_delay (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_address (struct docg3*,int) ; 
 int /*<<< orphan*/  doc_flash_command (struct docg3*,int /*<<< orphan*/ ) ; 
 int doc_read_seek (struct docg3*,int,int,int,int,int) ; 
 int doc_reset_seq (struct docg3*) ; 
 int /*<<< orphan*/  doc_set_device_id (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_wait_ready (struct docg3*) ; 
 int /*<<< orphan*/  doc_writeb (struct docg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int doc_read_page_prepare(struct docg3 *docg3, int block0, int block1,
				 int page, int offset)
{
	int wear_area = 0, ret = 0;

	doc_dbg("doc_read_page_prepare(blocks=(%d,%d), page=%d, ofsInPage=%d)\n",
		block0, block1, page, offset);
	if (offset >= DOC_LAYOUT_WEAR_OFFSET)
		wear_area = 1;
	if (!wear_area && offset > (DOC_LAYOUT_PAGE_OOB_SIZE * 2))
		return -EINVAL;

	doc_set_device_id(docg3, docg3->device_id);
	ret = doc_reset_seq(docg3);
	if (ret)
		goto err;

	/* Program the flash address block and page */
	ret = doc_read_seek(docg3, block0, block1, page, wear_area, offset);
	if (ret)
		goto err;

	doc_flash_command(docg3, DOC_CMD_READ_ALL_PLANES);
	doc_delay(docg3, 2);
	doc_wait_ready(docg3);

	doc_flash_command(docg3, DOC_CMD_SET_ADDR_READ);
	doc_delay(docg3, 1);
	if (offset >= DOC_LAYOUT_PAGE_SIZE * 2)
		offset -= 2 * DOC_LAYOUT_PAGE_SIZE;
	doc_flash_address(docg3, offset >> 2);
	doc_delay(docg3, 1);
	doc_wait_ready(docg3);

	doc_flash_command(docg3, DOC_CMD_READ_FLASH);

	return 0;
err:
	doc_writeb(docg3, 0, DOC_DATAEND);
	doc_delay(docg3, 2);
	return -EIO;
}