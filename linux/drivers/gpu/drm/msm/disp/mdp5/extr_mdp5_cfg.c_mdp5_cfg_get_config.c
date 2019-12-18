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
struct mdp5_cfg {int dummy; } ;
struct mdp5_cfg_handler {struct mdp5_cfg config; } ;

/* Variables and functions */

struct mdp5_cfg *mdp5_cfg_get_config(struct mdp5_cfg_handler *cfg_handler)
{
	return &cfg_handler->config;
}