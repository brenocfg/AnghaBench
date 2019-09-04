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
typedef  int u_int ;
struct layer2 {int next_id; int tei; int sapi; } ;

/* Variables and functions */

__attribute__((used)) static u_int
l2_newid(struct layer2 *l2)
{
	u_int	id;

	id = l2->next_id++;
	if (id == 0x7fff)
		l2->next_id = 1;
	id <<= 16;
	id |= l2->tei << 8;
	id |= l2->sapi;
	return id;
}