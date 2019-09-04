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
typedef  int /*<<< orphan*/  u8 ;
struct st33zp24_i2c_phy {int /*<<< orphan*/ * buf; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write8_reg(void *phy_id, u8 tpm_register, u8 *tpm_data, int tpm_size)
{
	struct st33zp24_i2c_phy *phy = phy_id;

	phy->buf[0] = tpm_register;
	memcpy(phy->buf + 1, tpm_data, tpm_size);
	return i2c_master_send(phy->client, phy->buf, tpm_size + 1);
}