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
struct ipw2100_priv {int dummy; } ;
struct ipw2100_fw {int /*<<< orphan*/ * fw_entry; scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipw2100_release_firmware(struct ipw2100_priv *priv,
				     struct ipw2100_fw *fw)
{
	fw->version = 0;
	release_firmware(fw->fw_entry);
	fw->fw_entry = NULL;
}