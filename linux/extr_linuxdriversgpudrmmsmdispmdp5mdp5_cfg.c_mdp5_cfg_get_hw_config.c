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
struct mdp5_cfg_hw {int dummy; } ;
struct TYPE_2__ {struct mdp5_cfg_hw const* hw; } ;
struct mdp5_cfg_handler {TYPE_1__ config; } ;

/* Variables and functions */

const struct mdp5_cfg_hw *mdp5_cfg_get_hw_config(struct mdp5_cfg_handler *cfg_handler)
{
	return cfg_handler->config.hw;
}