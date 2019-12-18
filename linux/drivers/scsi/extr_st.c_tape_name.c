#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct scsi_tape {TYPE_1__* disk; } ;
struct TYPE_2__ {char* disk_name; } ;

/* Variables and functions */

__attribute__((used)) static inline char *tape_name(struct scsi_tape *tape)
{
	return tape->disk->disk_name;
}