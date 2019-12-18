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
typedef  int /*<<< orphan*/  u_char ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct flchip {int /*<<< orphan*/  mutex; int /*<<< orphan*/  start; int /*<<< orphan*/  state; } ;
struct cfi_private {int /*<<< orphan*/  device_type; int /*<<< orphan*/  addr_unlock1; int /*<<< orphan*/  addr_unlock2; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FL_LOCKING ; 
 int /*<<< orphan*/  FL_READY ; 
 int /*<<< orphan*/  UDELAY (struct map_info*,struct flchip*,int /*<<< orphan*/ ,int) ; 
 int cfi_read_query (struct map_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct map_info*,struct cfi_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ chip_ready (struct map_info*,struct flchip*,scalar_t__) ; 
 int get_chip (struct map_info*,struct flchip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_chip (struct map_info*,struct flchip*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int do_otp_lock(struct map_info *map, struct flchip *chip, loff_t adr,
		       size_t len, u_char *buf, size_t grouplen)
{
	struct cfi_private *cfi = map->fldrv_priv;
	uint8_t lockreg;
	unsigned long timeo;
	int ret;

	/* make sure area matches group boundaries */
	if ((adr != 0) || (len != grouplen))
		return -EINVAL;

	mutex_lock(&chip->mutex);
	ret = get_chip(map, chip, chip->start, FL_LOCKING);
	if (ret) {
		mutex_unlock(&chip->mutex);
		return ret;
	}
	chip->state = FL_LOCKING;

	/* Enter lock register command */
	cfi_send_gen_cmd(0xAA, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);
	cfi_send_gen_cmd(0x55, cfi->addr_unlock2, chip->start, map, cfi,
			 cfi->device_type, NULL);
	cfi_send_gen_cmd(0x40, cfi->addr_unlock1, chip->start, map, cfi,
			 cfi->device_type, NULL);

	/* read lock register */
	lockreg = cfi_read_query(map, 0);

	/* set bit 0 to protect extended memory block */
	lockreg &= ~0x01;

	/* set bit 0 to protect extended memory block */
	/* write lock register */
	map_write(map, CMD(0xA0), chip->start);
	map_write(map, CMD(lockreg), chip->start);

	/* wait for chip to become ready */
	timeo = jiffies + msecs_to_jiffies(2);
	for (;;) {
		if (chip_ready(map, chip, adr))
			break;

		if (time_after(jiffies, timeo)) {
			pr_err("Waiting for chip to be ready timed out.\n");
			ret = -EIO;
			break;
		}
		UDELAY(map, chip, 0, 1);
	}

	/* exit protection commands */
	map_write(map, CMD(0x90), chip->start);
	map_write(map, CMD(0x00), chip->start);

	chip->state = FL_READY;
	put_chip(map, chip, chip->start);
	mutex_unlock(&chip->mutex);

	return ret;
}