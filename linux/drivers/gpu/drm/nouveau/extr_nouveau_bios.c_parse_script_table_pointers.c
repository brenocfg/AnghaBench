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
typedef  size_t uint16_t ;
struct nvbios {int /*<<< orphan*/ * data; int /*<<< orphan*/  init_script_tbls_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROM16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_script_table_pointers(struct nvbios *bios, uint16_t offset)
{
	/*
	 * Parses the init table segment for pointers used in script execution.
	 *
	 * offset + 0  (16 bits): init script tables pointer
	 * offset + 2  (16 bits): macro index table pointer
	 * offset + 4  (16 bits): macro table pointer
	 * offset + 6  (16 bits): condition table pointer
	 * offset + 8  (16 bits): io condition table pointer
	 * offset + 10 (16 bits): io flag condition table pointer
	 * offset + 12 (16 bits): init function table pointer
	 */

	bios->init_script_tbls_ptr = ROM16(bios->data[offset]);
}