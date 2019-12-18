#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct usb_ftdi {int* response; int received; int* bulk_in_buffer; int bulk_in_left; int bulk_in_last; int expected; struct u132_target* target; TYPE_1__* udev; scalar_t__ ed_found; struct u132_respond* respond; int /*<<< orphan*/  respond_head; int /*<<< orphan*/  bulk_in_size; int /*<<< orphan*/  bulk_in_endpointAddr; } ;
struct u132_target {int halted; int skipped; int toggle_bits; int error_count; int condition_code; } ;
struct u132_respond {int* value; int /*<<< orphan*/  wait_completion; scalar_t__* result; } ;
typedef  int /*<<< orphan*/  diag ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EILSEQ ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int RESPOND_MASK ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  ftdi_elan_do_callback (struct usb_ftdi*,struct u132_target*,int*,int) ; 
 int* have_ed_get_response (struct usb_ftdi*,struct u132_target*,int,int,int,int*) ; 
 int* have_ed_set_response (struct usb_ftdi*,struct u132_target*,int,int,int,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_elan_respond_engine(struct usb_ftdi *ftdi)
{
	u8 *b = ftdi->response + ftdi->received;
	int bytes_read = 0;
	int retry_on_empty = 1;
	int retry_on_timeout = 3;
read:{
		int packet_bytes = 0;
		int retval = usb_bulk_msg(ftdi->udev,
					  usb_rcvbulkpipe(ftdi->udev, ftdi->bulk_in_endpointAddr),
					  ftdi->bulk_in_buffer, ftdi->bulk_in_size,
					  &packet_bytes, 500);
		char diag[30 *3 + 4];
		char *d = diag;
		int m = packet_bytes;
		u8 *c = ftdi->bulk_in_buffer;
		int s = (sizeof(diag) - 1) / 3;
		diag[0] = 0;
		while (s-- > 0 && m-- > 0) {
			if (s > 0 || m == 0) {
				d += sprintf(d, " %02X", *c++);
			} else
				d += sprintf(d, " ..");
		}
		if (packet_bytes > 2) {
			ftdi->bulk_in_left = packet_bytes - 2;
			ftdi->bulk_in_last = 1;
			goto have;
		} else if (retval == -ETIMEDOUT) {
			if (retry_on_timeout-- > 0) {
				dev_err(&ftdi->udev->dev, "TIMED OUT with packet_bytes = %d with total %d bytes%s\n",
					packet_bytes, bytes_read, diag);
				goto more;
			} else if (bytes_read > 0) {
				dev_err(&ftdi->udev->dev, "ONLY %d bytes%s\n",
					bytes_read, diag);
				return -ENOMEM;
			} else {
				dev_err(&ftdi->udev->dev, "TIMED OUT with packet_bytes = %d with total %d bytes%s\n",
					packet_bytes, bytes_read, diag);
				return -ENOMEM;
			}
		} else if (retval == -EILSEQ) {
			dev_err(&ftdi->udev->dev, "error = %d with packet_bytes = %d with total %d bytes%s\n",
				retval, packet_bytes, bytes_read, diag);
			return retval;
		} else if (retval) {
			dev_err(&ftdi->udev->dev, "error = %d with packet_bytes = %d with total %d bytes%s\n",
				retval, packet_bytes, bytes_read, diag);
			return retval;
		} else {
			if (retry_on_empty-- > 0) {
				goto more;
			} else
				return 0;
		}
	}
more:{
		goto read;
	}
have:if (ftdi->bulk_in_left > 0) {
		u8 c = ftdi->bulk_in_buffer[++ftdi->bulk_in_last];
		bytes_read += 1;
		ftdi->bulk_in_left -= 1;
		if (ftdi->received == 0 && c == 0xFF) {
			goto have;
		} else
			*b++ = c;
		if (++ftdi->received < ftdi->expected) {
			goto have;
		} else if (ftdi->ed_found) {
			int ed_number = (ftdi->response[0] >> 5) & 0x03;
			u16 ed_length = (ftdi->response[2] << 8) |
				ftdi->response[1];
			struct u132_target *target = &ftdi->target[ed_number];
			int payload = (ed_length >> 0) & 0x07FF;
			char diag[30 *3 + 4];
			char *d = diag;
			int m = payload;
			u8 *c = 4 + ftdi->response;
			int s = (sizeof(diag) - 1) / 3;
			diag[0] = 0;
			while (s-- > 0 && m-- > 0) {
				if (s > 0 || m == 0) {
					d += sprintf(d, " %02X", *c++);
				} else
					d += sprintf(d, " ..");
			}
			ftdi_elan_do_callback(ftdi, target, 4 + ftdi->response,
					      payload);
			ftdi->received = 0;
			ftdi->expected = 4;
			ftdi->ed_found = 0;
			b = ftdi->response;
			goto have;
		} else if (ftdi->expected == 8) {
			u8 buscmd;
			int respond_head = ftdi->respond_head++;
			struct u132_respond *respond = &ftdi->respond[
				RESPOND_MASK & respond_head];
			u32 data = ftdi->response[7];
			data <<= 8;
			data |= ftdi->response[6];
			data <<= 8;
			data |= ftdi->response[5];
			data <<= 8;
			data |= ftdi->response[4];
			*respond->value = data;
			*respond->result = 0;
			complete(&respond->wait_completion);
			ftdi->received = 0;
			ftdi->expected = 4;
			ftdi->ed_found = 0;
			b = ftdi->response;
			buscmd = (ftdi->response[0] >> 0) & 0x0F;
			if (buscmd == 0x00) {
			} else if (buscmd == 0x02) {
			} else if (buscmd == 0x06) {
			} else if (buscmd == 0x0A) {
			} else
				dev_err(&ftdi->udev->dev, "Uxxx unknown(%0X) value = %08X\n",
					buscmd, data);
			goto have;
		} else {
			if ((ftdi->response[0] & 0x80) == 0x00) {
				ftdi->expected = 8;
				goto have;
			} else {
				int ed_number = (ftdi->response[0] >> 5) & 0x03;
				int ed_type = (ftdi->response[0] >> 0) & 0x03;
				u16 ed_length = (ftdi->response[2] << 8) |
					ftdi->response[1];
				struct u132_target *target = &ftdi->target[
					ed_number];
				target->halted = (ftdi->response[0] >> 3) &
					0x01;
				target->skipped = (ftdi->response[0] >> 2) &
					0x01;
				target->toggle_bits = (ftdi->response[3] >> 6)
					& 0x03;
				target->error_count = (ftdi->response[3] >> 4)
					& 0x03;
				target->condition_code = (ftdi->response[
								  3] >> 0) & 0x0F;
				if ((ftdi->response[0] & 0x10) == 0x00) {
					b = have_ed_set_response(ftdi, target,
								 ed_length, ed_number, ed_type,
								 b);
					goto have;
				} else {
					b = have_ed_get_response(ftdi, target,
								 ed_length, ed_number, ed_type,
								 b);
					goto have;
				}
			}
		}
	} else
		goto more;
}