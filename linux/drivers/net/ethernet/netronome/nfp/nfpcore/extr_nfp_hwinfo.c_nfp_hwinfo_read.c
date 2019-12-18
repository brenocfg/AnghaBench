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
struct nfp_hwinfo {int dummy; } ;
struct nfp_cpp {int dummy; } ;

/* Variables and functions */
 int hwinfo_db_validate (struct nfp_cpp*,struct nfp_hwinfo*,size_t) ; 
 struct nfp_hwinfo* hwinfo_fetch (struct nfp_cpp*,size_t*) ; 
 int /*<<< orphan*/  kfree (struct nfp_hwinfo*) ; 

struct nfp_hwinfo *nfp_hwinfo_read(struct nfp_cpp *cpp)
{
	struct nfp_hwinfo *db;
	size_t hwdb_size = 0;
	int err;

	db = hwinfo_fetch(cpp, &hwdb_size);
	if (!db)
		return NULL;

	err = hwinfo_db_validate(cpp, db, hwdb_size);
	if (err) {
		kfree(db);
		return NULL;
	}

	return db;
}