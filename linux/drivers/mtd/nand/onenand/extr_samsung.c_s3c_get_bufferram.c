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
struct onenand_chip {int /*<<< orphan*/  writesize; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; struct onenand_chip* priv; } ;
struct TYPE_2__ {unsigned char* page_buf; unsigned char* oob_buf; } ;

/* Variables and functions */
 int ONENAND_CURRENT_BUFFERRAM (struct onenand_chip*) ; 
 int ONENAND_DATARAM ; 
 TYPE_1__* onenand ; 

__attribute__((used)) static unsigned char *s3c_get_bufferram(struct mtd_info *mtd, int area)
{
	struct onenand_chip *this = mtd->priv;
	int index = ONENAND_CURRENT_BUFFERRAM(this);
	unsigned char *p;

	if (area == ONENAND_DATARAM) {
		p = onenand->page_buf;
		if (index == 1)
			p += this->writesize;
	} else {
		p = onenand->oob_buf;
		if (index == 1)
			p += mtd->oobsize;
	}

	return p;
}