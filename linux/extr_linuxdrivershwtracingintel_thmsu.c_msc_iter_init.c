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
struct msc_iter {int start_block; int block; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct msc_iter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void msc_iter_init(struct msc_iter *iter)
{
	memset(iter, 0, sizeof(*iter));
	iter->start_block = -1;
	iter->block = -1;
}