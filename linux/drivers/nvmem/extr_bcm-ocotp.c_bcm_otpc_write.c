#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct otpc_priv {scalar_t__ base; int /*<<< orphan*/  dev; TYPE_2__* map; TYPE_1__* config; } ;
struct TYPE_4__ {int otpc_row_size; scalar_t__* data_w_offset; } ;
struct TYPE_3__ {unsigned int word_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  OTPC_CMD_PROGRAM ; 
 int /*<<< orphan*/  OTPC_STAT_CMD_DONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  disable_ocotp_program (scalar_t__) ; 
 int enable_ocotp_program (scalar_t__) ; 
 int poll_cpu_status (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_start_bit (scalar_t__) ; 
 int /*<<< orphan*/  set_command (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cpu_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_start_bit (scalar_t__) ; 
 int /*<<< orphan*/  writel (size_t,scalar_t__) ; 

__attribute__((used)) static int bcm_otpc_write(void *context, unsigned int offset, void *val,
	size_t bytes)
{
	struct otpc_priv *priv = context;
	u32 *buf = val;
	u32 bytes_written;
	u32 address = offset / priv->config->word_size;
	int i, ret;

	if (offset % priv->config->word_size)
		return -EINVAL;

	ret = enable_ocotp_program(priv->base);
	if (ret)
		return -EIO;

	for (bytes_written = 0; bytes_written < bytes;) {
		set_command(priv->base, OTPC_CMD_PROGRAM);
		set_cpu_address(priv->base, address++);
		for (i = 0; i < priv->map->otpc_row_size; i++) {
			writel(*buf, priv->base + priv->map->data_w_offset[i]);
			buf++;
			bytes_written += sizeof(*buf);
		}
		set_start_bit(priv->base);
		ret = poll_cpu_status(priv->base, OTPC_STAT_CMD_DONE);
		reset_start_bit(priv->base);
		if (ret) {
			dev_err(priv->dev, "otp write error: 0x%x", ret);
			return -EIO;
		}
	}

	disable_ocotp_program(priv->base);

	return 0;
}