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
typedef  int /*<<< orphan*/  u8 ;
struct touchpad_protocol {unsigned int number_of_fingers; } ;
struct spi_packet {scalar_t__ flags; scalar_t__ device; int /*<<< orphan*/  data; int /*<<< orphan*/  length; int /*<<< orphan*/  remaining; int /*<<< orphan*/  offset; } ;
struct message {int /*<<< orphan*/  length; struct touchpad_protocol touchpad; int /*<<< orphan*/  keyboard; } ;
struct applespi_data {int read_active; int write_active; unsigned int saved_msg_len; TYPE_1__* spi; scalar_t__ msg_buf; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/  cmd_msg_lock; int /*<<< orphan*/  drain_complete; scalar_t__ drain; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int APPLESPI_PACKET_SIZE ; 
 unsigned int MAX_FINGERS ; 
 unsigned int MAX_PKTS_PER_MSG ; 
 unsigned int MSG_HEADER_SIZE ; 
 scalar_t__ PACKET_DEV_KEYB ; 
 scalar_t__ PACKET_DEV_TPAD ; 
 scalar_t__ PACKET_TYPE_READ ; 
 scalar_t__ PACKET_TYPE_WRITE ; 
 int /*<<< orphan*/  applespi_debug_print_read_packet (struct applespi_data*,struct spi_packet*) ; 
 int /*<<< orphan*/  applespi_handle_cmd_response (struct applespi_data*,struct spi_packet*,struct message*) ; 
 int /*<<< orphan*/  applespi_handle_keyboard_event (struct applespi_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  applespi_msg_complete (struct applespi_data*,int,int) ; 
 int /*<<< orphan*/  applespi_verify_crc (struct applespi_data*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  fingers ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  report_tp_state (struct applespi_data*,struct touchpad_protocol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 size_t struct_size (struct touchpad_protocol*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void applespi_got_data(struct applespi_data *applespi)
{
	struct spi_packet *packet;
	struct message *message;
	unsigned int msg_len;
	unsigned int off;
	unsigned int rem;
	unsigned int len;

	/* process packet header */
	if (!applespi_verify_crc(applespi, applespi->rx_buffer,
				 APPLESPI_PACKET_SIZE)) {
		unsigned long flags;

		spin_lock_irqsave(&applespi->cmd_msg_lock, flags);

		if (applespi->drain) {
			applespi->read_active = false;
			applespi->write_active = false;

			wake_up_all(&applespi->drain_complete);
		}

		spin_unlock_irqrestore(&applespi->cmd_msg_lock, flags);

		return;
	}

	packet = (struct spi_packet *)applespi->rx_buffer;

	applespi_debug_print_read_packet(applespi, packet);

	off = le16_to_cpu(packet->offset);
	rem = le16_to_cpu(packet->remaining);
	len = le16_to_cpu(packet->length);

	if (len > sizeof(packet->data)) {
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (invalid packet length %u)\n",
				     len);
		goto msg_complete;
	}

	/* handle multi-packet messages */
	if (rem > 0 || off > 0) {
		if (off != applespi->saved_msg_len) {
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received unexpected offset (got %u, expected %u)\n",
					     off, applespi->saved_msg_len);
			goto msg_complete;
		}

		if (off + rem > MAX_PKTS_PER_MSG * APPLESPI_PACKET_SIZE) {
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received message too large (size %u)\n",
					     off + rem);
			goto msg_complete;
		}

		if (off + len > MAX_PKTS_PER_MSG * APPLESPI_PACKET_SIZE) {
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received message too large (size %u)\n",
					     off + len);
			goto msg_complete;
		}

		memcpy(applespi->msg_buf + off, &packet->data, len);
		applespi->saved_msg_len += len;

		if (rem > 0)
			return;

		message = (struct message *)applespi->msg_buf;
		msg_len = applespi->saved_msg_len;
	} else {
		message = (struct message *)&packet->data;
		msg_len = len;
	}

	/* got complete message - verify */
	if (!applespi_verify_crc(applespi, (u8 *)message, msg_len))
		goto msg_complete;

	if (le16_to_cpu(message->length) != msg_len - MSG_HEADER_SIZE - 2) {
		dev_warn_ratelimited(&applespi->spi->dev,
				     "Received corrupted packet (invalid message length %u - expected %u)\n",
				     le16_to_cpu(message->length),
				     msg_len - MSG_HEADER_SIZE - 2);
		goto msg_complete;
	}

	/* handle message */
	if (packet->flags == PACKET_TYPE_READ &&
	    packet->device == PACKET_DEV_KEYB) {
		applespi_handle_keyboard_event(applespi, &message->keyboard);

	} else if (packet->flags == PACKET_TYPE_READ &&
		   packet->device == PACKET_DEV_TPAD) {
		struct touchpad_protocol *tp;
		size_t tp_len;

		tp = &message->touchpad;
		tp_len = struct_size(tp, fingers, tp->number_of_fingers);

		if (le16_to_cpu(message->length) + 2 != tp_len) {
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Received corrupted packet (invalid message length %u - num-fingers %u, tp-len %zu)\n",
					     le16_to_cpu(message->length),
					     tp->number_of_fingers, tp_len);
			goto msg_complete;
		}

		if (tp->number_of_fingers > MAX_FINGERS) {
			dev_warn_ratelimited(&applespi->spi->dev,
					     "Number of reported fingers (%u) exceeds max (%u))\n",
					     tp->number_of_fingers,
					     MAX_FINGERS);
			tp->number_of_fingers = MAX_FINGERS;
		}

		report_tp_state(applespi, tp);

	} else if (packet->flags == PACKET_TYPE_WRITE) {
		applespi_handle_cmd_response(applespi, packet, message);
	}

msg_complete:
	applespi->saved_msg_len = 0;

	applespi_msg_complete(applespi, packet->flags == PACKET_TYPE_WRITE,
			      true);
}