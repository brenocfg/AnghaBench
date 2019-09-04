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
struct pciefd_board {size_t can_count; int /*<<< orphan*/ * can; } ;

/* Variables and functions */
 int /*<<< orphan*/  pciefd_can_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pciefd_can_remove_all(struct pciefd_board *pciefd)
{
	while (pciefd->can_count > 0)
		pciefd_can_remove(pciefd->can[--pciefd->can_count]);
}