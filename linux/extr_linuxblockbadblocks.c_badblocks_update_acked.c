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
typedef  int /*<<< orphan*/  u64 ;
struct badblocks {int count; scalar_t__ unacked_exist; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_ACK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void badblocks_update_acked(struct badblocks *bb)
{
	u64 *p = bb->page;
	int i;
	bool unacked = false;

	if (!bb->unacked_exist)
		return;

	for (i = 0; i < bb->count ; i++) {
		if (!BB_ACK(p[i])) {
			unacked = true;
			break;
		}
	}

	if (!unacked)
		bb->unacked_exist = 0;
}