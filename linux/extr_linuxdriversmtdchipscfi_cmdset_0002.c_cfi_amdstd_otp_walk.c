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
struct otp_info {size_t start; size_t length; int locked; } ;
struct mtd_info {struct map_info* priv; } ;
struct map_info {struct cfi_private* fldrv_priv; } ;
struct flchip {unsigned long start; int /*<<< orphan*/  mutex; } ;
struct cfi_private {int interleave; int device_type; int numchips; int /*<<< orphan*/  addr_unlock1; int /*<<< orphan*/  addr_unlock2; struct flchip* chips; } ;
typedef  int (* otp_op_t ) (struct map_info*,struct flchip*,size_t,size_t,int /*<<< orphan*/ *,size_t) ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FL_CFI_QUERY ; 
 int /*<<< orphan*/  FL_LOCKING ; 
 int /*<<< orphan*/  cfi_qry_mode_off (unsigned long,struct map_info*,struct cfi_private*) ; 
 int /*<<< orphan*/  cfi_qry_mode_on (unsigned long,struct map_info*,struct cfi_private*) ; 
 int cfi_read_query (struct map_info*,unsigned long) ; 
 int /*<<< orphan*/  cfi_send_gen_cmd (int,int /*<<< orphan*/ ,unsigned long,struct map_info*,struct cfi_private*,int,int /*<<< orphan*/ *) ; 
 int get_chip (struct map_info*,struct flchip*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_m29ew (struct cfi_private*) ; 
 int /*<<< orphan*/  map_write (struct map_info*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_chip (struct map_info*,struct flchip*,unsigned long) ; 

__attribute__((used)) static int cfi_amdstd_otp_walk(struct mtd_info *mtd, loff_t from, size_t len,
			       size_t *retlen, u_char *buf,
			       otp_op_t action, int user_regs)
{
	struct map_info *map = mtd->priv;
	struct cfi_private *cfi = map->fldrv_priv;
	int ofs_factor = cfi->interleave * cfi->device_type;
	unsigned long base;
	int chipnum;
	struct flchip *chip;
	uint8_t otp, lockreg;
	int ret;

	size_t user_size, factory_size, otpsize;
	loff_t user_offset, factory_offset, otpoffset;
	int user_locked = 0, otplocked;

	*retlen = 0;

	for (chipnum = 0; chipnum < cfi->numchips; chipnum++) {
		chip = &cfi->chips[chipnum];
		factory_size = 0;
		user_size = 0;

		/* Micron M29EW family */
		if (is_m29ew(cfi)) {
			base = chip->start;

			/* check whether secsi area is factory locked
			   or user lockable */
			mutex_lock(&chip->mutex);
			ret = get_chip(map, chip, base, FL_CFI_QUERY);
			if (ret) {
				mutex_unlock(&chip->mutex);
				return ret;
			}
			cfi_qry_mode_on(base, map, cfi);
			otp = cfi_read_query(map, base + 0x3 * ofs_factor);
			cfi_qry_mode_off(base, map, cfi);
			put_chip(map, chip, base);
			mutex_unlock(&chip->mutex);

			if (otp & 0x80) {
				/* factory locked */
				factory_offset = 0;
				factory_size = 0x100;
			} else {
				/* customer lockable */
				user_offset = 0;
				user_size = 0x100;

				mutex_lock(&chip->mutex);
				ret = get_chip(map, chip, base, FL_LOCKING);
				if (ret) {
					mutex_unlock(&chip->mutex);
					return ret;
				}

				/* Enter lock register command */
				cfi_send_gen_cmd(0xAA, cfi->addr_unlock1,
						 chip->start, map, cfi,
						 cfi->device_type, NULL);
				cfi_send_gen_cmd(0x55, cfi->addr_unlock2,
						 chip->start, map, cfi,
						 cfi->device_type, NULL);
				cfi_send_gen_cmd(0x40, cfi->addr_unlock1,
						 chip->start, map, cfi,
						 cfi->device_type, NULL);
				/* read lock register */
				lockreg = cfi_read_query(map, 0);
				/* exit protection commands */
				map_write(map, CMD(0x90), chip->start);
				map_write(map, CMD(0x00), chip->start);
				put_chip(map, chip, chip->start);
				mutex_unlock(&chip->mutex);

				user_locked = ((lockreg & 0x01) == 0x00);
			}
		}

		otpsize = user_regs ? user_size : factory_size;
		if (!otpsize)
			continue;
		otpoffset = user_regs ? user_offset : factory_offset;
		otplocked = user_regs ? user_locked : 1;

		if (!action) {
			/* return otpinfo */
			struct otp_info *otpinfo;
			len -= sizeof(*otpinfo);
			if (len <= 0)
				return -ENOSPC;
			otpinfo = (struct otp_info *)buf;
			otpinfo->start = from;
			otpinfo->length = otpsize;
			otpinfo->locked = otplocked;
			buf += sizeof(*otpinfo);
			*retlen += sizeof(*otpinfo);
			from += otpsize;
		} else if ((from < otpsize) && (len > 0)) {
			size_t size;
			size = (len < otpsize - from) ? len : otpsize - from;
			ret = action(map, chip, otpoffset + from, size, buf,
				     otpsize);
			if (ret < 0)
				return ret;

			buf += size;
			len -= size;
			*retlen += size;
			from = 0;
		} else {
			from -= otpsize;
		}
	}
	return 0;
}