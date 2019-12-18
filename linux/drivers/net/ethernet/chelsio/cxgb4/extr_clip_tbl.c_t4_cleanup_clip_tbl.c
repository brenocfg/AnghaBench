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
struct clip_tbl {struct clip_tbl* cl_list; } ;
struct adapter {struct clip_tbl* clipt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct clip_tbl*) ; 

void t4_cleanup_clip_tbl(struct adapter *adap)
{
	struct clip_tbl *ctbl = adap->clipt;

	if (ctbl) {
		if (ctbl->cl_list)
			kvfree(ctbl->cl_list);
		kvfree(ctbl);
	}
}