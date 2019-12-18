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
struct pms7003_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SLEEP ; 
 int /*<<< orphan*/  pms7003_do_cmd (struct pms7003_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pms7003_stop(void *data)
{
	struct pms7003_state *state = data;

	pms7003_do_cmd(state, CMD_SLEEP);
}