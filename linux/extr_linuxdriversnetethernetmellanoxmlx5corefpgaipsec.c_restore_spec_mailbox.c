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
struct mailbox_mod {scalar_t__ saved_esp_id; int /*<<< orphan*/  saved_action; int /*<<< orphan*/  saved_outer_esp_spi_value; } ;
struct TYPE_2__ {uintptr_t esp_id; int /*<<< orphan*/  action; } ;
struct fs_fte {TYPE_1__ action; int /*<<< orphan*/  val; } ;

/* Variables and functions */
 char* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  misc_parameters ; 
 int /*<<< orphan*/  outer_esp_spi ; 

__attribute__((used)) static void restore_spec_mailbox(struct fs_fte *fte,
				 struct mailbox_mod *mbox_mod)
{
	char *misc_params_v = MLX5_ADDR_OF(fte_match_param,
					   fte->val,
					   misc_parameters);

	MLX5_SET(fte_match_set_misc, misc_params_v, outer_esp_spi,
		 mbox_mod->saved_outer_esp_spi_value);
	fte->action.action |= mbox_mod->saved_action;
	fte->action.esp_id = (uintptr_t)mbox_mod->saved_esp_id;
}