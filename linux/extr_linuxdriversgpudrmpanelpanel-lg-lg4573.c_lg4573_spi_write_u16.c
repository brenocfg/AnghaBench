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
typedef  int /*<<< orphan*/  u16 ;
struct spi_transfer {int len; int /*<<< orphan*/ * tx_buf; } ;
struct spi_message {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct lg4573 {int /*<<< orphan*/  spi; TYPE_1__ panel; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int lg4573_spi_write_u16(struct lg4573 *ctx, u16 data)
{
	struct spi_transfer xfer = {
		.len = 2,
	};
	u16 temp = cpu_to_be16(data);
	struct spi_message msg;

	dev_dbg(ctx->panel.dev, "writing data: %x\n", data);
	xfer.tx_buf = &temp;
	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	return spi_sync(ctx->spi, &msg);
}