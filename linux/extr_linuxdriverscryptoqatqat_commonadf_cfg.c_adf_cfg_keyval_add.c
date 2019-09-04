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
struct adf_cfg_section {int /*<<< orphan*/  param_head; } ;
struct adf_cfg_key_val {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adf_cfg_keyval_add(struct adf_cfg_key_val *new,
			       struct adf_cfg_section *sec)
{
	list_add_tail(&new->list, &sec->param_head);
}