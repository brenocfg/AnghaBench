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
struct descriptor {int control; } ;
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  DESCRIPTOR_BRANCH_ALWAYS ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct descriptor *find_branch_descriptor(struct descriptor *d, int z)
{
	__le16 branch;

	branch = d->control & cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS);

	/* figure out which descriptor the branch address goes in */
	if (z == 2 && branch == cpu_to_le16(DESCRIPTOR_BRANCH_ALWAYS))
		return d;
	else
		return d + z - 1;
}