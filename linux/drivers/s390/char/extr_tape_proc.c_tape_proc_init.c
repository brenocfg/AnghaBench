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
 int /*<<< orphan*/  proc_create_seq (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tape_proc_devices ; 
 int /*<<< orphan*/  tape_proc_seq ; 

void
tape_proc_init(void)
{
	tape_proc_devices = proc_create_seq("tapedevices", 0444, NULL,
					    &tape_proc_seq);
}