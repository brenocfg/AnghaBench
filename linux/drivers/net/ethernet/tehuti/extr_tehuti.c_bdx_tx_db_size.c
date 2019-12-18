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
struct txdb {int wptr; int rptr; int size; } ;

/* Variables and functions */

__attribute__((used)) static inline int bdx_tx_db_size(struct txdb *db)
{
	int taken = db->wptr - db->rptr;
	if (taken < 0)
		taken = db->size + 1 + taken;	/* (size + 1) equals memsz */

	return db->size - taken;
}