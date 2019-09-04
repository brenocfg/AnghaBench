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
struct firmware {int /*<<< orphan*/  priv; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_fw_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void firmware_free_data(const struct firmware *fw)
{
	/* Loaded directly? */
	if (!fw->priv) {
		vfree(fw->data);
		return;
	}
	free_fw_priv(fw->priv);
}