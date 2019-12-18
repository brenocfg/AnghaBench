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
struct iwl_drv {int dummy; } ;
struct fw_desc {scalar_t__ len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_free_fw_desc(struct iwl_drv *drv, struct fw_desc *desc)
{
	vfree(desc->data);
	desc->data = NULL;
	desc->len = 0;
}