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
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static inline void
_debug_dump_reply(void *mpi_request, int sz)
{
	int i;
	__le32 *mfp = (__le32 *)mpi_request;

	pr_info("reply:\n\t");
	for (i = 0; i < sz; i++) {
		if (i && ((i % 8) == 0))
			pr_info("\n\t");
		pr_info("%08x ", le32_to_cpu(mfp[i]));
	}
	pr_info("\n");
}