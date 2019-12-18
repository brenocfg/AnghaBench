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
struct ks_net {int /*<<< orphan*/  cmd_reg_cache; int /*<<< orphan*/  cmd_reg_cache_int; } ;

/* Variables and functions */

__attribute__((used)) static inline void ks_save_cmd_reg(struct ks_net *ks)
{
	/*ks8851 MLL has a bug to read back the command register.
	* So rely on software to save the content of command register.
	*/
	ks->cmd_reg_cache_int = ks->cmd_reg_cache;
}