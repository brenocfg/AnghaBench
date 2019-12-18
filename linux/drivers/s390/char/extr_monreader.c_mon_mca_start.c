#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rmmsg; } ;
struct mon_msg {TYPE_1__ msg; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long mon_mca_start(struct mon_msg *monmsg)
{
	return *(u32 *) &monmsg->msg.rmmsg;
}