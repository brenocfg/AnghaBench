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
struct data_descriptor_entry {unsigned int count; int /*<<< orphan*/  address; int /*<<< orphan*/  length; scalar_t__ index; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nx842_get_pa (struct data_descriptor_entry*) ; 

__attribute__((used)) static void setup_indirect_dde(struct data_descriptor_entry *dde,
			       struct data_descriptor_entry *ddl,
			       unsigned int dde_count, unsigned int byte_count)
{
	dde->flags = 0;
	dde->count = dde_count;
	dde->index = 0;
	dde->length = cpu_to_be32(byte_count);
	dde->address = cpu_to_be64(nx842_get_pa(ddl));
}