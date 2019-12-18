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
struct siw_mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_mem_put (struct siw_mem*) ; 

__attribute__((used)) static inline void siw_unref_mem_sgl(struct siw_mem **mem, unsigned int num_sge)
{
	while (num_sge) {
		if (*mem == NULL)
			break;

		siw_mem_put(*mem);
		*mem = NULL;
		mem++;
		num_sge--;
	}
}