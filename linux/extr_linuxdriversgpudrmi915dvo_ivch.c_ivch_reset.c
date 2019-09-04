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
struct ivch_priv {int* reg_backup; } ;
struct intel_dvo_device {struct ivch_priv* dev_priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  VR10 ; 
 int /*<<< orphan*/ * backup_addresses ; 
 int /*<<< orphan*/  ivch_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ivch_reset(struct intel_dvo_device *dvo)
{
	struct ivch_priv *priv = dvo->dev_priv;
	int i;

	DRM_DEBUG_KMS("Resetting the IVCH registers\n");

	ivch_write(dvo, VR10, 0x0000);

	for (i = 0; i < ARRAY_SIZE(backup_addresses); i++)
		ivch_write(dvo, backup_addresses[i], priv->reg_backup[i]);
}