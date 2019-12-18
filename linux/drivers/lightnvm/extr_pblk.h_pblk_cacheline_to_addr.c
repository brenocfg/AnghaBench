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
struct TYPE_2__ {int line; int is_cached; } ;
struct ppa_addr {TYPE_1__ c; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ppa_addr pblk_cacheline_to_addr(int addr)
{
	struct ppa_addr p;

	p.c.line = addr;
	p.c.is_cached = 1;

	return p;
}