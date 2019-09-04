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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct fsi_master_gpio {int /*<<< orphan*/  t_send_delay; int /*<<< orphan*/  dev; } ;
struct fsi_gpio_msg {int msg; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int /*<<< orphan*/  FSI_CRC_ERR_RETRIES ; 
 int /*<<< orphan*/  FSI_MASTER_DPOLL_CLOCKS ; 
 int /*<<< orphan*/  FSI_MASTER_EPOLL_CLOCKS ; 
 int /*<<< orphan*/  FSI_MASTER_MAX_BUSY ; 
#define  FSI_RESP_ACK 131 
#define  FSI_RESP_BUSY 130 
#define  FSI_RESP_ERRA 129 
#define  FSI_RESP_ERRC 128 
 int /*<<< orphan*/  build_dpoll_command (struct fsi_gpio_msg*,int) ; 
 int /*<<< orphan*/  build_epoll_command (struct fsi_gpio_msg*,int) ; 
 int /*<<< orphan*/  clock_zeros (struct fsi_master_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  echo_delay (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  issue_term (struct fsi_master_gpio*,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_one_response (struct fsi_master_gpio*,int,struct fsi_gpio_msg*,int*) ; 
 int /*<<< orphan*/  serial_out (struct fsi_master_gpio*,struct fsi_gpio_msg*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_crc_cmd_error (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_crc_rsp_error (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  trace_fsi_master_gpio_poll_response_busy (struct fsi_master_gpio*,int) ; 

__attribute__((used)) static int poll_for_response(struct fsi_master_gpio *master,
		uint8_t slave, uint8_t size, void *data)
{
	struct fsi_gpio_msg response, cmd;
	int busy_count = 0, rc, i;
	unsigned long flags;
	uint8_t tag;
	uint8_t *data_byte = data;
	int crc_err_retries = 0;
retry:
	rc = read_one_response(master, size, &response, &tag);

	/* Handle retries on CRC errors */
	if (rc == -EAGAIN) {
		/* Too many retries ? */
		if (crc_err_retries++ > FSI_CRC_ERR_RETRIES) {
			/*
			 * Pass it up as a -EIO otherwise upper level will retry
			 * the whole command which isn't what we want here.
			 */
			rc = -EIO;
			goto fail;
		}
		dev_dbg(master->dev,
			 "CRC error retry %d\n", crc_err_retries);
		trace_fsi_master_gpio_crc_rsp_error(master);
		build_epoll_command(&cmd, slave);
		local_irq_save(flags);
		clock_zeros(master, FSI_MASTER_EPOLL_CLOCKS);
		serial_out(master, &cmd);
		echo_delay(master);
		local_irq_restore(flags);
		goto retry;
	} else if (rc)
		goto fail;

	switch (tag) {
	case FSI_RESP_ACK:
		if (size && data) {
			uint64_t val = response.msg;
			/* clear crc & mask */
			val >>= 4;
			val &= (1ull << (size * 8)) - 1;

			for (i = 0; i < size; i++) {
				data_byte[size-i-1] = val;
				val >>= 8;
			}
		}
		break;
	case FSI_RESP_BUSY:
		/*
		 * Its necessary to clock slave before issuing
		 * d-poll, not indicated in the hardware protocol
		 * spec. < 20 clocks causes slave to hang, 21 ok.
		 */
		if (busy_count++ < FSI_MASTER_MAX_BUSY) {
			build_dpoll_command(&cmd, slave);
			local_irq_save(flags);
			clock_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
			serial_out(master, &cmd);
			echo_delay(master);
			local_irq_restore(flags);
			goto retry;
		}
		dev_warn(master->dev,
			"ERR slave is stuck in busy state, issuing TERM\n");
		local_irq_save(flags);
		clock_zeros(master, FSI_MASTER_DPOLL_CLOCKS);
		local_irq_restore(flags);
		issue_term(master, slave);
		rc = -EIO;
		break;

	case FSI_RESP_ERRA:
		dev_dbg(master->dev, "ERRA received: 0x%x\n", (int)response.msg);
		rc = -EIO;
		break;
	case FSI_RESP_ERRC:
		dev_dbg(master->dev, "ERRC received: 0x%x\n", (int)response.msg);
		trace_fsi_master_gpio_crc_cmd_error(master);
		rc = -EAGAIN;
		break;
	}

	if (busy_count > 0)
		trace_fsi_master_gpio_poll_response_busy(master, busy_count);
 fail:
	/*
	 * tSendDelay clocks, avoids signal reflections when switching
	 * from receive of response back to send of data.
	 */
	local_irq_save(flags);
	clock_zeros(master, master->t_send_delay);
	local_irq_restore(flags);

	return rc;
}