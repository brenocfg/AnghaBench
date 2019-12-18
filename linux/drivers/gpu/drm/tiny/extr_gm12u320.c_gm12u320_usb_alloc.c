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
struct TYPE_2__ {int /*<<< orphan*/  workq; } ;
struct gm12u320_device {int* data_buf; TYPE_1__ fb_update; int /*<<< orphan*/  cmd_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SIZE ; 
 int DATA_BLOCK_FOOTER_SIZE ; 
 int DATA_BLOCK_HEADER_SIZE ; 
 int DATA_BLOCK_SIZE ; 
 int DATA_LAST_BLOCK_SIZE ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GM12U320_BLOCK_COUNT ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 char const* data_block_footer ; 
 char* data_block_header ; 
 char* data_last_block_header ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 

__attribute__((used)) static int gm12u320_usb_alloc(struct gm12u320_device *gm12u320)
{
	int i, block_size;
	const char *hdr;

	gm12u320->cmd_buf = kmalloc(CMD_SIZE, GFP_KERNEL);
	if (!gm12u320->cmd_buf)
		return -ENOMEM;

	for (i = 0; i < GM12U320_BLOCK_COUNT; i++) {
		if (i == GM12U320_BLOCK_COUNT - 1) {
			block_size = DATA_LAST_BLOCK_SIZE;
			hdr = data_last_block_header;
		} else {
			block_size = DATA_BLOCK_SIZE;
			hdr = data_block_header;
		}

		gm12u320->data_buf[i] = kzalloc(block_size, GFP_KERNEL);
		if (!gm12u320->data_buf[i])
			return -ENOMEM;

		memcpy(gm12u320->data_buf[i], hdr, DATA_BLOCK_HEADER_SIZE);
		memcpy(gm12u320->data_buf[i] +
				(block_size - DATA_BLOCK_FOOTER_SIZE),
		       data_block_footer, DATA_BLOCK_FOOTER_SIZE);
	}

	gm12u320->fb_update.workq = create_singlethread_workqueue(DRIVER_NAME);
	if (!gm12u320->fb_update.workq)
		return -ENOMEM;

	return 0;
}