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
struct sps30_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPS30_STOP_MEAS ; 
 int /*<<< orphan*/  sps30_do_cmd (struct sps30_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sps30_stop_meas(void *data)
{
	struct sps30_state *state = data;

	sps30_do_cmd(state, SPS30_STOP_MEAS, NULL, 0);
}