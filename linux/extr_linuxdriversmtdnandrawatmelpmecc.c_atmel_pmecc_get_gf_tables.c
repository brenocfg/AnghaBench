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
struct TYPE_2__ {int sectorsize; } ;
struct atmel_pmecc_user_req {TYPE_1__ ecc; } ;
struct atmel_pmecc_gf_tables {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct atmel_pmecc_gf_tables const*) ; 
 struct atmel_pmecc_gf_tables* atmel_pmecc_create_gf_tables (struct atmel_pmecc_user_req const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct atmel_pmecc_gf_tables* pmecc_gf_tables_1024 ; 
 struct atmel_pmecc_gf_tables* pmecc_gf_tables_512 ; 
 int /*<<< orphan*/  pmecc_gf_tables_lock ; 

__attribute__((used)) static const struct atmel_pmecc_gf_tables *
atmel_pmecc_get_gf_tables(const struct atmel_pmecc_user_req *req)
{
	const struct atmel_pmecc_gf_tables **gf_tables, *ret;

	mutex_lock(&pmecc_gf_tables_lock);
	if (req->ecc.sectorsize == 512)
		gf_tables = &pmecc_gf_tables_512;
	else
		gf_tables = &pmecc_gf_tables_1024;

	ret = *gf_tables;

	if (!ret) {
		ret = atmel_pmecc_create_gf_tables(req);
		if (!IS_ERR(ret))
			*gf_tables = ret;
	}
	mutex_unlock(&pmecc_gf_tables_lock);

	return ret;
}