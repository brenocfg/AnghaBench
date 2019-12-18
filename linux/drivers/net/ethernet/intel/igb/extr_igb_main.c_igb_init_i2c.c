#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_12__ {int /*<<< orphan*/  name; TYPE_1__ dev; TYPE_5__* algo_data; int /*<<< orphan*/  owner; } ;
struct TYPE_11__ {struct igb_adapter* data; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_10__ {TYPE_3__ mac; } ;
struct igb_adapter {TYPE_6__ i2c_adap; TYPE_2__* pdev; TYPE_5__ i2c_algo; TYPE_4__ hw; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ e1000_i350 ; 
 int /*<<< orphan*/  i2c_bit_add_bus (TYPE_6__*) ; 
 TYPE_5__ igb_i2c_algo ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static s32 igb_init_i2c(struct igb_adapter *adapter)
{
	s32 status = 0;

	/* I2C interface supported on i350 devices */
	if (adapter->hw.mac.type != e1000_i350)
		return 0;

	/* Initialize the i2c bus which is controlled by the registers.
	 * This bus will use the i2c_algo_bit structue that implements
	 * the protocol through toggling of the 4 bits in the register.
	 */
	adapter->i2c_adap.owner = THIS_MODULE;
	adapter->i2c_algo = igb_i2c_algo;
	adapter->i2c_algo.data = adapter;
	adapter->i2c_adap.algo_data = &adapter->i2c_algo;
	adapter->i2c_adap.dev.parent = &adapter->pdev->dev;
	strlcpy(adapter->i2c_adap.name, "igb BB",
		sizeof(adapter->i2c_adap.name));
	status = i2c_bit_add_bus(&adapter->i2c_adap);
	return status;
}