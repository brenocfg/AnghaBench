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
struct nvbios_init {int link; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 

__attribute__((used)) static inline int
init_link(struct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->link)
			return init->link == 2;
		error("script needs OR link\n");
	}
	return 0;
}