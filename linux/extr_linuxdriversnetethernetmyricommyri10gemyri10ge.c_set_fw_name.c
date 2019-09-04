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
struct myri10ge_priv {int fw_name_allocated; char* fw_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (char*) ; 

__attribute__((used)) static void set_fw_name(struct myri10ge_priv *mgp, char *name, bool allocated)
{
	if (mgp->fw_name_allocated)
		kfree(mgp->fw_name);
	mgp->fw_name = name;
	mgp->fw_name_allocated = allocated;
}