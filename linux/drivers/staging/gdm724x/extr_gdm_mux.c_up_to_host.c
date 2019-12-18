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
typedef  int u32 ;
struct mux_rx {int offset; int len; int (* callback ) (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ buf; struct mux_dev* mux_dev; } ;
struct mux_pkt_header {int /*<<< orphan*/ * data; int /*<<< orphan*/  packet_type; int /*<<< orphan*/  payload_size; int /*<<< orphan*/  start_flag; } ;
struct mux_dev {int /*<<< orphan*/  tty_dev; } ;

/* Variables and functions */
 int ALIGN (unsigned int,int) ; 
 unsigned int MUX_HEADER_SIZE ; 
 int /*<<< orphan*/  RECV_PACKET_PROCESS_COMPLETE ; 
 int /*<<< orphan*/  RECV_PACKET_PROCESS_CONTINUE ; 
 unsigned int START_FLAG ; 
 int TO_HOST_BUFFER_REQUEST_FAIL ; 
 int TO_HOST_INVALID_PACKET ; 
 unsigned short __le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int packet_type_to_index (unsigned short) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int stub1 (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int up_to_host(struct mux_rx *r)
{
	struct mux_dev *mux_dev = r->mux_dev;
	struct mux_pkt_header *mux_header;
	unsigned int start_flag;
	unsigned int payload_size;
	unsigned short packet_type;
	int total_len;
	u32 packet_size_sum = r->offset;
	int index;
	int ret = TO_HOST_INVALID_PACKET;
	int len = r->len;

	while (1) {
		mux_header = (struct mux_pkt_header *)(r->buf +
						       packet_size_sum);
		start_flag = __le32_to_cpu(mux_header->start_flag);
		payload_size = __le32_to_cpu(mux_header->payload_size);
		packet_type = __le16_to_cpu(mux_header->packet_type);

		if (start_flag != START_FLAG) {
			pr_err("invalid START_FLAG %x\n", start_flag);
			break;
		}

		total_len = ALIGN(MUX_HEADER_SIZE + payload_size, 4);

		if (len - packet_size_sum < total_len) {
			pr_err("invalid payload : %d %d %04x\n",
			       payload_size, len, packet_type);
			break;
		}

		index = packet_type_to_index(packet_type);
		if (index < 0) {
			pr_err("invalid index %d\n", index);
			break;
		}

		ret = r->callback(mux_header->data,
				payload_size,
				index,
				mux_dev->tty_dev,
				RECV_PACKET_PROCESS_CONTINUE
				);
		if (ret == TO_HOST_BUFFER_REQUEST_FAIL) {
			r->offset += packet_size_sum;
			break;
		}

		packet_size_sum += total_len;
		if (len - packet_size_sum <= MUX_HEADER_SIZE + 2) {
			ret = r->callback(NULL,
					0,
					index,
					mux_dev->tty_dev,
					RECV_PACKET_PROCESS_COMPLETE
					);
			break;
		}
	}

	return ret;
}