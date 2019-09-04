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
struct TYPE_4__ {int bytes; scalar_t__ ooboffset; int sectorsize; int strength; int nsectors; } ;
struct atmel_pmecc_user_req {int pagesize; scalar_t__ oobsize; TYPE_2__ ecc; } ;
struct atmel_pmecc {TYPE_1__* caps; } ;
struct TYPE_3__ {int nstrengths; int* strengths; } ;

/* Variables and functions */
 int ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH ; 
 int ATMEL_PMECC_SECTOR_SIZE_AUTO ; 
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int fls (int) ; 

__attribute__((used)) static int atmel_pmecc_prepare_user_req(struct atmel_pmecc *pmecc,
					struct atmel_pmecc_user_req *req)
{
	int i, max_eccbytes, eccbytes = 0, eccstrength = 0;

	if (req->pagesize <= 0 || req->oobsize <= 0 || req->ecc.bytes <= 0)
		return -EINVAL;

	if (req->ecc.ooboffset >= 0 &&
	    req->ecc.ooboffset + req->ecc.bytes > req->oobsize)
		return -EINVAL;

	if (req->ecc.sectorsize == ATMEL_PMECC_SECTOR_SIZE_AUTO) {
		if (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH)
			return -EINVAL;

		if (req->pagesize > 512)
			req->ecc.sectorsize = 1024;
		else
			req->ecc.sectorsize = 512;
	}

	if (req->ecc.sectorsize != 512 && req->ecc.sectorsize != 1024)
		return -EINVAL;

	if (req->pagesize % req->ecc.sectorsize)
		return -EINVAL;

	req->ecc.nsectors = req->pagesize / req->ecc.sectorsize;

	max_eccbytes = req->ecc.bytes;

	for (i = 0; i < pmecc->caps->nstrengths; i++) {
		int nbytes, strength = pmecc->caps->strengths[i];

		if (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH &&
		    strength < req->ecc.strength)
			continue;

		nbytes = DIV_ROUND_UP(strength * fls(8 * req->ecc.sectorsize),
				      8);
		nbytes *= req->ecc.nsectors;

		if (nbytes > max_eccbytes)
			break;

		eccstrength = strength;
		eccbytes = nbytes;

		if (req->ecc.strength != ATMEL_PMECC_MAXIMIZE_ECC_STRENGTH)
			break;
	}

	if (!eccstrength)
		return -EINVAL;

	req->ecc.bytes = eccbytes;
	req->ecc.strength = eccstrength;

	if (req->ecc.ooboffset < 0)
		req->ecc.ooboffset = req->oobsize - eccbytes;

	return 0;
}