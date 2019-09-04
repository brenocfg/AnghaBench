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
typedef  int u16 ;
struct ivch_priv {int quiet; int width; int height; int* reg_backup; } ;
struct intel_dvo_device {int slave_addr; struct ivch_priv* dev_priv; struct i2c_adapter* i2c_bus; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VR00 ; 
 int VR00_BASE_ADDRESS_MASK ; 
 int /*<<< orphan*/  VR20 ; 
 int /*<<< orphan*/  VR21 ; 
 int /*<<< orphan*/ * backup_addresses ; 
 int /*<<< orphan*/  ivch_dump_regs (struct intel_dvo_device*) ; 
 int /*<<< orphan*/  ivch_read (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  kfree (struct ivch_priv*) ; 
 struct ivch_priv* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ivch_init(struct intel_dvo_device *dvo,
		      struct i2c_adapter *adapter)
{
	struct ivch_priv *priv;
	u16 temp;
	int i;

	priv = kzalloc(sizeof(struct ivch_priv), GFP_KERNEL);
	if (priv == NULL)
		return false;

	dvo->i2c_bus = adapter;
	dvo->dev_priv = priv;
	priv->quiet = true;

	if (!ivch_read(dvo, VR00, &temp))
		goto out;
	priv->quiet = false;

	/* Since the identification bits are probably zeroes, which doesn't seem
	 * very unique, check that the value in the base address field matches
	 * the address it's responding on.
	 */
	if ((temp & VR00_BASE_ADDRESS_MASK) != dvo->slave_addr) {
		DRM_DEBUG_KMS("ivch detect failed due to address mismatch "
			  "(%d vs %d)\n",
			  (temp & VR00_BASE_ADDRESS_MASK), dvo->slave_addr);
		goto out;
	}

	ivch_read(dvo, VR20, &priv->width);
	ivch_read(dvo, VR21, &priv->height);

	/* Make a backup of the registers to be able to restore them
	 * upon suspend.
	 */
	for (i = 0; i < ARRAY_SIZE(backup_addresses); i++)
		ivch_read(dvo, backup_addresses[i], priv->reg_backup + i);

	ivch_dump_regs(dvo);

	return true;

out:
	kfree(priv);
	return false;
}