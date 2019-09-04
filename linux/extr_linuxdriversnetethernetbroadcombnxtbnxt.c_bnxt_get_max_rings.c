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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  _bnxt_get_max_rings (struct bnxt*,int*,int*,int*) ; 
 int bnxt_trim_rings (struct bnxt*,int*,int*,int,int) ; 

int bnxt_get_max_rings(struct bnxt *bp, int *max_rx, int *max_tx, bool shared)
{
	int rx, tx, cp;

	_bnxt_get_max_rings(bp, &rx, &tx, &cp);
	*max_rx = rx;
	*max_tx = tx;
	if (!rx || !tx || !cp)
		return -ENOMEM;

	return bnxt_trim_rings(bp, max_rx, max_tx, cp, shared);
}