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
struct devlink {int dummy; } ;
struct bnxt_dl {struct bnxt* bp; } ;
struct bnxt {struct devlink* dl; } ;

/* Variables and functions */
 struct bnxt_dl* devlink_priv (struct devlink*) ; 

__attribute__((used)) static inline void bnxt_link_bp_to_dl(struct bnxt *bp, struct devlink *dl)
{
	bp->dl = dl;

	/* add a back pointer in dl to bp */
	if (dl) {
		struct bnxt_dl *bp_dl = devlink_priv(dl);

		bp_dl->bp = bp;
	}
}