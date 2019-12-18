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
struct iwl_priv {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  APMG_DIGITAL_SVR_REG ; 
 int /*<<< orphan*/  APMG_SVR_DIGITAL_VOLTAGE_1_32 ; 
 int /*<<< orphan*/  APMG_SVR_VOLTAGE_CONFIG_BIT_MSK ; 
 int /*<<< orphan*/  iwl_set_bits_mask_prph (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl1000_nic_config(struct iwl_priv *priv)
{
	/* Setting digital SVR for 1000 card to 1.32V */
	/* locking is acquired in iwl_set_bits_mask_prph() function */
	iwl_set_bits_mask_prph(priv->trans, APMG_DIGITAL_SVR_REG,
				APMG_SVR_DIGITAL_VOLTAGE_1_32,
				~APMG_SVR_VOLTAGE_CONFIG_BIT_MSK);
}