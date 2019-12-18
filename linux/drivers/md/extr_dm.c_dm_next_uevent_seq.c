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
typedef  int /*<<< orphan*/  uint32_t ;
struct mapped_device {int /*<<< orphan*/  uevent_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_return (int,int /*<<< orphan*/ *) ; 

uint32_t dm_next_uevent_seq(struct mapped_device *md)
{
	return atomic_add_return(1, &md->uevent_seq);
}