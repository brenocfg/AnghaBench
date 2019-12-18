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
struct TYPE_2__ {struct mtd_part* name; } ;
struct mtd_part {TYPE_1__ mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mtd_part*) ; 

__attribute__((used)) static inline void free_partition(struct mtd_part *p)
{
	kfree(p->mtd.name);
	kfree(p);
}