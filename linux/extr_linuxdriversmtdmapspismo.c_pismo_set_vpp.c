#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct pismo_data {int /*<<< orphan*/  vpp_data; int /*<<< orphan*/  (* vpp ) (int /*<<< orphan*/ ,int) ;} ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct pismo_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pismo_set_vpp(struct platform_device *pdev, int on)
{
	struct i2c_client *client = to_i2c_client(pdev->dev.parent);
	struct pismo_data *pismo = i2c_get_clientdata(client);

	pismo->vpp(pismo->vpp_data, on);
}