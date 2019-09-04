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

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt ; 
 int fdt_pack (scalar_t__) ; 
 int /*<<< orphan*/  fdt_strerror (int) ; 

__attribute__((used)) static unsigned long fdt_wrapper_finalize(void)
{
	int rc;

	rc = fdt_pack(fdt);
	if (rc != 0)
		fatal("Couldn't pack flat tree: %s\n\r",
		      fdt_strerror(rc));
	return (unsigned long)fdt;
}