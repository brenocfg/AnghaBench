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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int bbt_options; int /*<<< orphan*/  base; struct nand_bbt_descr* bbt_md; struct nand_bbt_descr* bbt_td; } ;
struct nand_bbt_descr {int options; int* pages; int* version; } ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int NAND_BBT_CREATE ; 
 int NAND_BBT_CREATE_EMPTY ; 
 int NAND_BBT_PERCHIP ; 
 int NAND_BBT_VERSION ; 
 int NAND_BBT_WRITE ; 
 int /*<<< orphan*/  create_bbt (struct nand_chip*,int /*<<< orphan*/ *,struct nand_bbt_descr*,int) ; 
 int max (int,int) ; 
 scalar_t__ mtd_is_bitflip (int) ; 
 scalar_t__ mtd_is_eccerr (int) ; 
 int nanddev_ntargets (int /*<<< orphan*/ *) ; 
 int read_abs_bbt (struct nand_chip*,int /*<<< orphan*/ *,struct nand_bbt_descr*,int) ; 
 int write_bbt (struct nand_chip*,int /*<<< orphan*/ *,struct nand_bbt_descr*,struct nand_bbt_descr*,int) ; 

__attribute__((used)) static int check_create(struct nand_chip *this, uint8_t *buf,
			struct nand_bbt_descr *bd)
{
	int i, chips, writeops, create, chipsel, res, res2;
	struct nand_bbt_descr *td = this->bbt_td;
	struct nand_bbt_descr *md = this->bbt_md;
	struct nand_bbt_descr *rd, *rd2;

	/* Do we have a bbt per chip? */
	if (td->options & NAND_BBT_PERCHIP)
		chips = nanddev_ntargets(&this->base);
	else
		chips = 1;

	for (i = 0; i < chips; i++) {
		writeops = 0;
		create = 0;
		rd = NULL;
		rd2 = NULL;
		res = res2 = 0;
		/* Per chip or per device? */
		chipsel = (td->options & NAND_BBT_PERCHIP) ? i : -1;
		/* Mirrored table available? */
		if (md) {
			if (td->pages[i] == -1 && md->pages[i] == -1) {
				create = 1;
				writeops = 0x03;
			} else if (td->pages[i] == -1) {
				rd = md;
				writeops = 0x01;
			} else if (md->pages[i] == -1) {
				rd = td;
				writeops = 0x02;
			} else if (td->version[i] == md->version[i]) {
				rd = td;
				if (!(td->options & NAND_BBT_VERSION))
					rd2 = md;
			} else if (((int8_t)(td->version[i] - md->version[i])) > 0) {
				rd = td;
				writeops = 0x02;
			} else {
				rd = md;
				writeops = 0x01;
			}
		} else {
			if (td->pages[i] == -1) {
				create = 1;
				writeops = 0x01;
			} else {
				rd = td;
			}
		}

		if (create) {
			/* Create the bad block table by scanning the device? */
			if (!(td->options & NAND_BBT_CREATE))
				continue;

			/* Create the table in memory by scanning the chip(s) */
			if (!(this->bbt_options & NAND_BBT_CREATE_EMPTY))
				create_bbt(this, buf, bd, chipsel);

			td->version[i] = 1;
			if (md)
				md->version[i] = 1;
		}

		/* Read back first? */
		if (rd) {
			res = read_abs_bbt(this, buf, rd, chipsel);
			if (mtd_is_eccerr(res)) {
				/* Mark table as invalid */
				rd->pages[i] = -1;
				rd->version[i] = 0;
				i--;
				continue;
			}
		}
		/* If they weren't versioned, read both */
		if (rd2) {
			res2 = read_abs_bbt(this, buf, rd2, chipsel);
			if (mtd_is_eccerr(res2)) {
				/* Mark table as invalid */
				rd2->pages[i] = -1;
				rd2->version[i] = 0;
				i--;
				continue;
			}
		}

		/* Scrub the flash table(s)? */
		if (mtd_is_bitflip(res) || mtd_is_bitflip(res2))
			writeops = 0x03;

		/* Update version numbers before writing */
		if (md) {
			td->version[i] = max(td->version[i], md->version[i]);
			md->version[i] = td->version[i];
		}

		/* Write the bad block table to the device? */
		if ((writeops & 0x01) && (td->options & NAND_BBT_WRITE)) {
			res = write_bbt(this, buf, td, md, chipsel);
			if (res < 0)
				return res;
		}

		/* Write the mirror bad block table to the device? */
		if ((writeops & 0x02) && md && (md->options & NAND_BBT_WRITE)) {
			res = write_bbt(this, buf, md, td, chipsel);
			if (res < 0)
				return res;
		}
	}
	return 0;
}