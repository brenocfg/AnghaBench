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
 scalar_t__* config ; 
 int configured ; 
 scalar_t__ final_ack ; 
 scalar_t__ isspace (scalar_t__) ; 
 int kgdb_register_io_module (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdbts_io_ops ; 
 int /*<<< orphan*/  kgdbts_run_tests () ; 
 int /*<<< orphan*/  run_plant_and_detach_test (int) ; 
 int /*<<< orphan*/  strlen (scalar_t__*) ; 

__attribute__((used)) static int configure_kgdbts(void)
{
	int err = 0;

	if (!strlen(config) || isspace(config[0]))
		goto noconfig;

	final_ack = 0;
	run_plant_and_detach_test(1);

	err = kgdb_register_io_module(&kgdbts_io_ops);
	if (err) {
		configured = 0;
		return err;
	}
	configured = 1;
	kgdbts_run_tests();

	return err;

noconfig:
	config[0] = 0;
	configured = 0;

	return err;
}