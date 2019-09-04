#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int strength; int bytes; int nsectors; int sectorsize; scalar_t__ ooboffset; } ;
struct atmel_pmecc_user_req {TYPE_3__ ecc; scalar_t__ oobsize; } ;
struct TYPE_5__ {int cfg; scalar_t__ eaddr; scalar_t__ saddr; scalar_t__ sarea; } ;
struct atmel_pmecc_user {int eccbytes; TYPE_2__ cache; struct atmel_pmecc_gf_tables const* gf_tables; int /*<<< orphan*/ * dmu; int /*<<< orphan*/ * delta; int /*<<< orphan*/ * mu; struct atmel_pmecc_user* smu; struct atmel_pmecc_user* lmu; struct atmel_pmecc_user* si; struct atmel_pmecc_user* partial_syn; struct atmel_pmecc* pmecc; } ;
struct atmel_pmecc_gf_tables {int dummy; } ;
struct atmel_pmecc {TYPE_1__* caps; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  struct atmel_pmecc_user s16 ;
struct TYPE_4__ {int nstrengths; int* strengths; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int ENOMEM ; 
 struct atmel_pmecc_user* ERR_CAST (struct atmel_pmecc_gf_tables const*) ; 
 struct atmel_pmecc_user* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct atmel_pmecc_gf_tables const*) ; 
 int PMECC_CFG_BCH_STRENGTH (int) ; 
 int PMECC_CFG_NSECTORS (int) ; 
 int PMECC_CFG_SECTOR1024 ; 
 scalar_t__ PTR_ALIGN (struct atmel_pmecc_user*,int) ; 
 struct atmel_pmecc_gf_tables* atmel_pmecc_get_gf_tables (struct atmel_pmecc_user_req*) ; 
 int atmel_pmecc_prepare_user_req (struct atmel_pmecc*,struct atmel_pmecc_user_req*) ; 
 int /*<<< orphan*/  kfree (struct atmel_pmecc_user*) ; 
 struct atmel_pmecc_user* kzalloc (int,int /*<<< orphan*/ ) ; 

struct atmel_pmecc_user *
atmel_pmecc_create_user(struct atmel_pmecc *pmecc,
			struct atmel_pmecc_user_req *req)
{
	struct atmel_pmecc_user *user;
	const struct atmel_pmecc_gf_tables *gf_tables;
	int strength, size, ret;

	ret = atmel_pmecc_prepare_user_req(pmecc, req);
	if (ret)
		return ERR_PTR(ret);

	size = sizeof(*user);
	size = ALIGN(size, sizeof(u16));
	/* Reserve space for partial_syn, si and smu */
	size += ((2 * req->ecc.strength) + 1) * sizeof(u16) *
		(2 + req->ecc.strength + 2);
	/* Reserve space for lmu. */
	size += (req->ecc.strength + 1) * sizeof(u16);
	/* Reserve space for mu, dmu and delta. */
	size = ALIGN(size, sizeof(s32));
	size += (req->ecc.strength + 1) * sizeof(s32) * 3;

	user = kzalloc(size, GFP_KERNEL);
	if (!user)
		return ERR_PTR(-ENOMEM);

	user->pmecc = pmecc;

	user->partial_syn = (s16 *)PTR_ALIGN(user + 1, sizeof(u16));
	user->si = user->partial_syn + ((2 * req->ecc.strength) + 1);
	user->lmu = user->si + ((2 * req->ecc.strength) + 1);
	user->smu = user->lmu + (req->ecc.strength + 1);
	user->mu = (s32 *)PTR_ALIGN(user->smu +
				    (((2 * req->ecc.strength) + 1) *
				     (req->ecc.strength + 2)),
				    sizeof(s32));
	user->dmu = user->mu + req->ecc.strength + 1;
	user->delta = user->dmu + req->ecc.strength + 1;

	gf_tables = atmel_pmecc_get_gf_tables(req);
	if (IS_ERR(gf_tables)) {
		kfree(user);
		return ERR_CAST(gf_tables);
	}

	user->gf_tables = gf_tables;

	user->eccbytes = req->ecc.bytes / req->ecc.nsectors;

	for (strength = 0; strength < pmecc->caps->nstrengths; strength++) {
		if (pmecc->caps->strengths[strength] == req->ecc.strength)
			break;
	}

	user->cache.cfg = PMECC_CFG_BCH_STRENGTH(strength) |
			  PMECC_CFG_NSECTORS(req->ecc.nsectors);

	if (req->ecc.sectorsize == 1024)
		user->cache.cfg |= PMECC_CFG_SECTOR1024;

	user->cache.sarea = req->oobsize - 1;
	user->cache.saddr = req->ecc.ooboffset;
	user->cache.eaddr = req->ecc.ooboffset + req->ecc.bytes - 1;

	return user;
}