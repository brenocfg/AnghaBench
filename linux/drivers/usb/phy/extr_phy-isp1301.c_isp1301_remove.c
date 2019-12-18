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
struct isp1301 {int /*<<< orphan*/  phy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct isp1301* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/ * isp1301_i2c_client ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int isp1301_remove(struct i2c_client *client)
{
	struct isp1301 *isp = i2c_get_clientdata(client);

	usb_remove_phy(&isp->phy);
	isp1301_i2c_client = NULL;

	return 0;
}