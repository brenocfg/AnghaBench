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
struct mon_msg {int mca_offset; scalar_t__ pos; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int mon_mca_size (struct mon_msg*) ; 

__attribute__((used)) static inline void mon_next_mca(struct mon_msg *monmsg)
{
	if (likely((mon_mca_size(monmsg) - monmsg->mca_offset) == 12))
		return;
	monmsg->mca_offset += 12;
	monmsg->pos = 0;
}