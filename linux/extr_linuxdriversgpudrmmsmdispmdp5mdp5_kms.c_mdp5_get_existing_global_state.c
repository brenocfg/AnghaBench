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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct mdp5_kms {TYPE_1__ glob_state; } ;
struct mdp5_global_state {int dummy; } ;

/* Variables and functions */
 struct mdp5_global_state* to_mdp5_global_state (int /*<<< orphan*/ ) ; 

struct mdp5_global_state *
mdp5_get_existing_global_state(struct mdp5_kms *mdp5_kms)
{
	return to_mdp5_global_state(mdp5_kms->glob_state.state);
}