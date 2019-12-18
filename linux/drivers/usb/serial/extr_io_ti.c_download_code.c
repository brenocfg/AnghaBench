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
struct edgeport_serial {int /*<<< orphan*/  serial; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EDGE_FW_BULK_MAX_PACKET_SIZE ; 
 int bulk_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int download_code(struct edgeport_serial *serial, __u8 *image,
							int image_length)
{
	int status = 0;
	int pos;
	int transfer;
	int done;

	/* Transfer firmware image */
	for (pos = 0; pos < image_length; ) {
		/* Read the next buffer from file */
		transfer = image_length - pos;
		if (transfer > EDGE_FW_BULK_MAX_PACKET_SIZE)
			transfer = EDGE_FW_BULK_MAX_PACKET_SIZE;

		/* Transfer data */
		status = bulk_xfer(serial->serial, &image[pos],
							transfer, &done);
		if (status)
			break;
		/* Advance buffer pointer */
		pos += done;
	}

	return status;
}