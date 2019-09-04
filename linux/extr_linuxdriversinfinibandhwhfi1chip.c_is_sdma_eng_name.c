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
 unsigned int TXE_NUM_SDMA_ENGINES ; 
 scalar_t__ likely (int) ; 
 char** sdma_int_names ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static char *is_sdma_eng_name(char *buf, size_t bsize, unsigned int source)
{
	/* what interrupt */
	unsigned int what  = source / TXE_NUM_SDMA_ENGINES;
	/* which engine */
	unsigned int which = source % TXE_NUM_SDMA_ENGINES;

	if (likely(what < 3))
		snprintf(buf, bsize, "%s%u", sdma_int_names[what], which);
	else
		snprintf(buf, bsize, "Invalid SDMA interrupt %u", source);
	return buf;
}