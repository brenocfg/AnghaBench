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
typedef  int /*<<< orphan*/  u32 ;
struct ks_wlan_private {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ROM_BUFF_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ks7010_sdio_read (struct ks_wlan_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ks7010_sdio_data_compare(struct ks_wlan_private *priv, u32 address,
				    u8 *data, unsigned int size)
{
	int ret;
	u8 *read_buf;

	read_buf = kmalloc(ROM_BUFF_SIZE, GFP_KERNEL);
	if (!read_buf)
		return -ENOMEM;

	ret = ks7010_sdio_read(priv, address, read_buf, size);
	if (ret)
		goto err_free_read_buf;

	if (memcmp(data, read_buf, size) != 0) {
		ret = -EIO;
		netdev_err(priv->net_dev, "data compare error (%d)\n", ret);
		goto err_free_read_buf;
	}

	return 0;

err_free_read_buf:
	kfree(read_buf);

	return ret;
}