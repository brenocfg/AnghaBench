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
typedef  int /*<<< orphan*/  u32 ;
struct bnx2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2_free_skbs (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_init_all_rings (struct bnx2*) ; 
 int bnx2_init_chip (struct bnx2*) ; 
 int bnx2_reset_chip (struct bnx2*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnx2_reset_nic(struct bnx2 *bp, u32 reset_code)
{
	int rc;

	rc = bnx2_reset_chip(bp, reset_code);
	bnx2_free_skbs(bp);
	if (rc)
		return rc;

	if ((rc = bnx2_init_chip(bp)) != 0)
		return rc;

	bnx2_init_all_rings(bp);
	return 0;
}