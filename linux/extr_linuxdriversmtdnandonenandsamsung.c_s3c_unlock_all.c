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
struct onenand_chip {size_t chipsize; int options; int /*<<< orphan*/  (* wait ) (struct mtd_info*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* command ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mtd_info {struct onenand_chip* priv; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FL_LOCKING ; 
 int /*<<< orphan*/  ONENAND_CMD_UNLOCK ; 
 int /*<<< orphan*/  ONENAND_CMD_UNLOCK_ALL ; 
 int ONENAND_HAS_UNLOCK_ALL ; 
 int /*<<< orphan*/  ONENAND_IS_DDP (struct onenand_chip*) ; 
 int /*<<< orphan*/  s3c_onenand_check_lock_status (struct mtd_info*) ; 
 int /*<<< orphan*/  s3c_onenand_do_lock_cmd (struct mtd_info*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_unlock_all(struct mtd_info *mtd)
{
	struct onenand_chip *this = mtd->priv;
	loff_t ofs = 0;
	size_t len = this->chipsize;

	if (this->options & ONENAND_HAS_UNLOCK_ALL) {
		/* Write unlock command */
		this->command(mtd, ONENAND_CMD_UNLOCK_ALL, 0, 0);

		/* No need to check return value */
		this->wait(mtd, FL_LOCKING);

		/* Workaround for all block unlock in DDP */
		if (!ONENAND_IS_DDP(this)) {
			s3c_onenand_check_lock_status(mtd);
			return;
		}

		/* All blocks on another chip */
		ofs = this->chipsize >> 1;
		len = this->chipsize >> 1;
	}

	s3c_onenand_do_lock_cmd(mtd, ofs, len, ONENAND_CMD_UNLOCK);

	s3c_onenand_check_lock_status(mtd);
}