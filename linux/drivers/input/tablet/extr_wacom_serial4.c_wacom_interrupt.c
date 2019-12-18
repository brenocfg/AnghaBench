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
struct wacom {int idx; int* data; TYPE_1__* dev; } ;
struct serio {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DATA_SIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PACKET_LENGTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct wacom* serio_get_drvdata (struct serio*) ; 
 int /*<<< orphan*/  wacom_clear_data_buf (struct wacom*) ; 
 int /*<<< orphan*/  wacom_handle_packet (struct wacom*) ; 
 int /*<<< orphan*/  wacom_handle_response (struct wacom*) ; 

__attribute__((used)) static irqreturn_t wacom_interrupt(struct serio *serio, unsigned char data,
				   unsigned int flags)
{
	struct wacom *wacom = serio_get_drvdata(serio);

	if (data & 0x80)
		wacom->idx = 0;

	/*
	 * We're either expecting a carriage return-terminated ASCII
	 * response string, or a seven-byte packet with the MSB set on
	 * the first byte.
	 *
	 * Note however that some tablets (the PenPartner, for
	 * example) don't send a carriage return at the end of a
	 * command.  We handle these by waiting for timeout.
	 */
	if (data == '\r' && !(wacom->data[0] & 0x80)) {
		wacom_handle_response(wacom);
		wacom_clear_data_buf(wacom);
		return IRQ_HANDLED;
	}

	/* Leave place for 0 termination */
	if (wacom->idx > (DATA_SIZE - 2)) {
		dev_dbg(&wacom->dev->dev,
			"throwing away %d bytes of garbage\n", wacom->idx);
		wacom_clear_data_buf(wacom);
	}
	wacom->data[wacom->idx++] = data;

	if (wacom->idx == PACKET_LENGTH && (wacom->data[0] & 0x80)) {
		wacom_handle_packet(wacom);
		wacom_clear_data_buf(wacom);
	}

	return IRQ_HANDLED;
}