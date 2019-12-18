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
struct onenand_chip {int /*<<< orphan*/  oob_buf; int /*<<< orphan*/  (* read_bufferram ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mtd_info {int /*<<< orphan*/  oobsize; struct onenand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ONENAND_SPARERAM ; 
 int mtd_ooblayout_get_databytes (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int onenand_transfer_auto_oob(struct mtd_info *mtd, uint8_t *buf, int column,
				int thislen)
{
	struct onenand_chip *this = mtd->priv;
	int ret;

	this->read_bufferram(mtd, ONENAND_SPARERAM, this->oob_buf, 0,
			     mtd->oobsize);
	ret = mtd_ooblayout_get_databytes(mtd, buf, this->oob_buf,
					  column, thislen);
	if (ret)
		return ret;

	return 0;
}