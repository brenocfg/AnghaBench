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
struct mdp5_cfg_handler {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mdp5_cfg_handler*) ; 

void mdp5_cfg_destroy(struct mdp5_cfg_handler *cfg_handler)
{
	kfree(cfg_handler);
}