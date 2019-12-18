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
struct i2c_piix4_adapdata {int port; scalar_t__ smba; } ;
struct i2c_adapter {int port; scalar_t__ smba; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBIOSIZE ; 
 int /*<<< orphan*/  i2c_del_adapter (struct i2c_piix4_adapdata*) ; 
 struct i2c_piix4_adapdata* i2c_get_adapdata (struct i2c_piix4_adapdata*) ; 
 int /*<<< orphan*/  kfree (struct i2c_piix4_adapdata*) ; 
 int piix4_port_shift_sb800 ; 
 int /*<<< orphan*/  release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void piix4_adap_remove(struct i2c_adapter *adap)
{
	struct i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);

	if (adapdata->smba) {
		i2c_del_adapter(adap);
		if (adapdata->port == (0 << piix4_port_shift_sb800))
			release_region(adapdata->smba, SMBIOSIZE);
		kfree(adapdata);
		kfree(adap);
	}
}