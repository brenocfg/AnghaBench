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
struct ring_desc {int /*<<< orphan*/  list; } ;
struct pic32_sqi {int /*<<< orphan*/  bd_list_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ring_desc_put(struct pic32_sqi *sqi, struct ring_desc *rdesc)
{
	list_move(&rdesc->list, &sqi->bd_list_free);
}