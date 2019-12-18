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
typedef  int u8 ;
struct ks8995_switch {TYPE_2__* spi; void* revision_id; TYPE_1__* chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int family_id; int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIPID_M ; 
 int EIO ; 
 int ENODEV ; 
#define  FAMILY_KS8995 129 
#define  FAMILY_KSZ8795 128 
 int /*<<< orphan*/  KS8995_REG_ID0 ; 
 int /*<<< orphan*/  KS8995_REG_ID1 ; 
 int /*<<< orphan*/  KSZ8864_CHIP_ID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  get_chip_id (int) ; 
 void* get_chip_rev (int) ; 
 int ks8995_read_reg (struct ks8995_switch*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ks8995_get_revision(struct ks8995_switch *ks)
{
	int err;
	u8 id0, id1, ksz8864_id;

	/* read family id */
	err = ks8995_read_reg(ks, KS8995_REG_ID0, &id0);
	if (err) {
		err = -EIO;
		goto err_out;
	}

	/* verify family id */
	if (id0 != ks->chip->family_id) {
		dev_err(&ks->spi->dev, "chip family id mismatch: expected 0x%02x but 0x%02x read\n",
			ks->chip->family_id, id0);
		err = -ENODEV;
		goto err_out;
	}

	switch (ks->chip->family_id) {
	case FAMILY_KS8995:
		/* try reading chip id at CHIP ID1 */
		err = ks8995_read_reg(ks, KS8995_REG_ID1, &id1);
		if (err) {
			err = -EIO;
			goto err_out;
		}

		/* verify chip id */
		if ((get_chip_id(id1) == CHIPID_M) &&
		    (get_chip_id(id1) == ks->chip->chip_id)) {
			/* KS8995MA */
			ks->revision_id = get_chip_rev(id1);
		} else if (get_chip_id(id1) != CHIPID_M) {
			/* KSZ8864RMN */
			err = ks8995_read_reg(ks, KS8995_REG_ID1, &ksz8864_id);
			if (err) {
				err = -EIO;
				goto err_out;
			}

			if ((ksz8864_id & 0x80) &&
			    (ks->chip->chip_id == KSZ8864_CHIP_ID)) {
				ks->revision_id = get_chip_rev(id1);
			}

		} else {
			dev_err(&ks->spi->dev, "unsupported chip id for KS8995 family: 0x%02x\n",
				id1);
			err = -ENODEV;
		}
		break;
	case FAMILY_KSZ8795:
		/* try reading chip id at CHIP ID1 */
		err = ks8995_read_reg(ks, KS8995_REG_ID1, &id1);
		if (err) {
			err = -EIO;
			goto err_out;
		}

		if (get_chip_id(id1) == ks->chip->chip_id) {
			ks->revision_id = get_chip_rev(id1);
		} else {
			dev_err(&ks->spi->dev, "unsupported chip id for KSZ8795 family: 0x%02x\n",
				id1);
			err = -ENODEV;
		}
		break;
	default:
		dev_err(&ks->spi->dev, "unsupported family id: 0x%02x\n", id0);
		err = -ENODEV;
		break;
	}
err_out:
	return err;
}