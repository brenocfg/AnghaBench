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
struct INFTLrecord {int nb_blocks; int* VUtable; int* PUtable; } ;

/* Variables and functions */
 int BLOCK_NIL ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

void INFTL_dumpVUchains(struct INFTLrecord *s)
{
	int logical, block, i;

	pr_debug("-------------------------------------------"
		"----------------------------------\n");

	pr_debug("INFTL Virtual Unit Chains:\n");
	for (logical = 0; logical < s->nb_blocks; logical++) {
		block = s->VUtable[logical];
		if (block >= s->nb_blocks)
			continue;
		pr_debug("  LOGICAL %d --> %d ", logical, block);
		for (i = 0; i < s->nb_blocks; i++) {
			if (s->PUtable[block] == BLOCK_NIL)
				break;
			block = s->PUtable[block];
			pr_debug("%d ", block);
		}
		pr_debug("\n");
	}

	pr_debug("-------------------------------------------"
		"----------------------------------\n");
}