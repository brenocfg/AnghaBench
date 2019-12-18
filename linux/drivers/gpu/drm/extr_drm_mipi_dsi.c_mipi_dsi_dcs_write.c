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
typedef  int /*<<< orphan*/  u8 ;
struct mipi_dsi_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  mipi_dsi_dcs_write_buffer (struct mipi_dsi_device*,int /*<<< orphan*/ *,size_t) ; 

ssize_t mipi_dsi_dcs_write(struct mipi_dsi_device *dsi, u8 cmd,
			   const void *data, size_t len)
{
	ssize_t err;
	size_t size;
	u8 *tx;

	if (len > 0) {
		size = 1 + len;

		tx = kmalloc(size, GFP_KERNEL);
		if (!tx)
			return -ENOMEM;

		/* concatenate the DCS command byte and the payload */
		tx[0] = cmd;
		memcpy(&tx[1], data, len);
	} else {
		tx = &cmd;
		size = 1;
	}

	err = mipi_dsi_dcs_write_buffer(dsi, tx, size);

	if (len > 0)
		kfree(tx);

	return err;
}