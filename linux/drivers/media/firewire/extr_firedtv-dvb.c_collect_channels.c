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
typedef  int /*<<< orphan*/  u16 ;
struct firedtv {int /*<<< orphan*/ * channel_pid; int /*<<< orphan*/  channel_active; } ;

/* Variables and functions */
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void collect_channels(struct firedtv *fdtv, int *pidc, u16 pid[])
{
	int i, n;

	for (i = 0, n = 0; i < 16; i++)
		if (test_bit(i, &fdtv->channel_active))
			pid[n++] = fdtv->channel_pid[i];
	*pidc = n;
}