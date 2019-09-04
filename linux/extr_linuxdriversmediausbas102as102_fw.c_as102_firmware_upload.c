#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_5__ {int* request; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; int /*<<< orphan*/  address; } ;
struct as10x_fw_pkt_t {TYPE_2__ u; TYPE_1__ raw; } ;
struct as10x_bus_adapter_t {TYPE_3__* ops; } ;
struct TYPE_6__ {int (* upload_fw_pkt ) (struct as10x_bus_adapter_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct as10x_fw_pkt_t*) ; 
 struct as10x_fw_pkt_t* kmalloc (int,int /*<<< orphan*/ ) ; 
 int parse_hex_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned char*) ; 
 int stub1 (struct as10x_bus_adapter_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int stub2 (struct as10x_bus_adapter_t*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int as102_firmware_upload(struct as10x_bus_adapter_t *bus_adap,
				 unsigned char *cmd,
				 const struct firmware *firmware) {

	struct as10x_fw_pkt_t *fw_pkt;
	int total_read_bytes = 0, errno = 0;
	unsigned char addr_has_changed = 0;

	fw_pkt = kmalloc(sizeof(*fw_pkt), GFP_KERNEL);
	if (!fw_pkt)
		return -ENOMEM;


	for (total_read_bytes = 0; total_read_bytes < firmware->size; ) {
		int read_bytes = 0, data_len = 0;

		/* parse intel hex line */
		read_bytes = parse_hex_line(
				(u8 *) (firmware->data + total_read_bytes),
				fw_pkt->raw.address,
				fw_pkt->raw.data,
				&data_len,
				&addr_has_changed);

		if (read_bytes <= 0)
			goto error;

		/* detect the end of file */
		total_read_bytes += read_bytes;
		if (total_read_bytes == firmware->size) {
			fw_pkt->u.request[0] = 0x00;
			fw_pkt->u.request[1] = 0x03;

			/* send EOF command */
			errno = bus_adap->ops->upload_fw_pkt(bus_adap,
							     (uint8_t *)
							     fw_pkt, 2, 0);
			if (errno < 0)
				goto error;
		} else {
			if (!addr_has_changed) {
				/* prepare command to send */
				fw_pkt->u.request[0] = 0x00;
				fw_pkt->u.request[1] = 0x01;

				data_len += sizeof(fw_pkt->u.request);
				data_len += sizeof(fw_pkt->raw.address);

				/* send cmd to device */
				errno = bus_adap->ops->upload_fw_pkt(bus_adap,
								     (uint8_t *)
								     fw_pkt,
								     data_len,
								     0);
				if (errno < 0)
					goto error;
			}
		}
	}
error:
	kfree(fw_pkt);
	return (errno == 0) ? total_read_bytes : errno;
}