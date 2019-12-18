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
struct us_data {unsigned char* iobuf; int /*<<< orphan*/  send_bulk_pipe; } ;

/* Variables and functions */
 unsigned char ALAUDA_BULK_CMD ; 
 unsigned char ALAUDA_BULK_RESET_MEDIA ; 
 unsigned char MEDIA_PORT (struct us_data*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int usb_stor_bulk_transfer_buf (struct us_data*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alauda_reset_media(struct us_data *us)
{
	unsigned char *command = us->iobuf;

	memset(command, 0, 9);
	command[0] = ALAUDA_BULK_CMD;
	command[1] = ALAUDA_BULK_RESET_MEDIA;
	command[8] = MEDIA_PORT(us);

	return usb_stor_bulk_transfer_buf(us, us->send_bulk_pipe,
		command, 9, NULL);
}