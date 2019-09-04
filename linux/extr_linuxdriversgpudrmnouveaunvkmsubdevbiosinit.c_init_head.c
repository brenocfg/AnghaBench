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
struct nvbios_init {scalar_t__ head; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ init_exec (struct nvbios_init*) ; 

__attribute__((used)) static inline int
init_head(struct nvbios_init *init)
{
	if (init_exec(init)) {
		if (init->head >= 0)
			return init->head;
		error("script needs head\n");
	}
	return 0;
}