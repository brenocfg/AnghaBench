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
struct log_header_disk {int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
struct log_header_core {int /*<<< orphan*/  nr_regions; void* version; void* magic; } ;

/* Variables and functions */
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void header_from_disk(struct log_header_core *core, struct log_header_disk *disk)
{
	core->magic = le32_to_cpu(disk->magic);
	core->version = le32_to_cpu(disk->version);
	core->nr_regions = le64_to_cpu(disk->nr_regions);
}