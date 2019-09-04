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
struct etap_pre_exec_data {int /*<<< orphan*/  control_me; int /*<<< orphan*/  data_me; int /*<<< orphan*/  control_remote; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void etap_pre_exec(void *arg)
{
	struct etap_pre_exec_data *data = arg;

	dup2(data->control_remote, 1);
	close(data->data_me);
	close(data->control_me);
}