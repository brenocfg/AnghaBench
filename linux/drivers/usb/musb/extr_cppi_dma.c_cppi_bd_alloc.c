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
struct cppi_descriptor {struct cppi_descriptor* next; } ;
struct cppi_channel {struct cppi_descriptor* freelist; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cppi_descriptor *cppi_bd_alloc(struct cppi_channel *c)
{
	struct cppi_descriptor	*bd = c->freelist;

	if (bd)
		c->freelist = bd->next;
	return bd;
}