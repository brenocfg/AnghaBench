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
struct log_header_disk {int /*<<< orphan*/  nr_regions; void* version; void* magic; } ;
struct log_header_core {int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void header_to_disk(struct log_header_core *core, struct log_header_disk *disk)
{
	disk->magic = cpu_to_le32(core->magic);
	disk->version = cpu_to_le32(core->version);
	disk->nr_regions = cpu_to_le64(core->nr_regions);
}