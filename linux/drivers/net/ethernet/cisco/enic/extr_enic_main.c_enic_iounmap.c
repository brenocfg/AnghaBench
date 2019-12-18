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
struct enic {TYPE_1__* bar; } ;
struct TYPE_2__ {scalar_t__ vaddr; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 

__attribute__((used)) static void enic_iounmap(struct enic *enic)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(enic->bar); i++)
		if (enic->bar[i].vaddr)
			iounmap(enic->bar[i].vaddr);
}