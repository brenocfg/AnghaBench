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
typedef  int u32 ;
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_eeprom {scalar_t__ magic; int offset; int len; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ EEPROM_MAGIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t3_seeprom_read (struct adapter*,int,int /*<<< orphan*/ *) ; 
 int t3_seeprom_wp (struct adapter*,int) ; 
 int t3_seeprom_write (struct adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_eeprom(struct net_device *dev, struct ethtool_eeprom *eeprom,
		      u8 * data)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	u32 aligned_offset, aligned_len;
	__le32 *p;
	u8 *buf;
	int err;

	if (eeprom->magic != EEPROM_MAGIC)
		return -EINVAL;

	aligned_offset = eeprom->offset & ~3;
	aligned_len = (eeprom->len + (eeprom->offset & 3) + 3) & ~3;

	if (aligned_offset != eeprom->offset || aligned_len != eeprom->len) {
		buf = kmalloc(aligned_len, GFP_KERNEL);
		if (!buf)
			return -ENOMEM;
		err = t3_seeprom_read(adapter, aligned_offset, (__le32 *) buf);
		if (!err && aligned_len > 4)
			err = t3_seeprom_read(adapter,
					      aligned_offset + aligned_len - 4,
					      (__le32 *) & buf[aligned_len - 4]);
		if (err)
			goto out;
		memcpy(buf + (eeprom->offset & 3), data, eeprom->len);
	} else
		buf = data;

	err = t3_seeprom_wp(adapter, 0);
	if (err)
		goto out;

	for (p = (__le32 *) buf; !err && aligned_len; aligned_len -= 4, p++) {
		err = t3_seeprom_write(adapter, aligned_offset, *p);
		aligned_offset += 4;
	}

	if (!err)
		err = t3_seeprom_wp(adapter, 1);
out:
	if (buf != data)
		kfree(buf);
	return err;
}