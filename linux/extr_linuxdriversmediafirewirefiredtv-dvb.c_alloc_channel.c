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
struct firedtv {int /*<<< orphan*/  channel_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  __test_and_set_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alloc_channel(struct firedtv *fdtv)
{
	int i;

	for (i = 0; i < 16; i++)
		if (!__test_and_set_bit(i, &fdtv->channel_active))
			break;
	return i;
}