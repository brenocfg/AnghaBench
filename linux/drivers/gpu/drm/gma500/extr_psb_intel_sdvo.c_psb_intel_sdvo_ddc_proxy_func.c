#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct psb_intel_sdvo {TYPE_2__* i2c; } ;
struct i2c_adapter {struct psb_intel_sdvo* algo_data; } ;
struct TYPE_4__ {TYPE_1__* algo; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* functionality ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static u32 psb_intel_sdvo_ddc_proxy_func(struct i2c_adapter *adapter)
{
	struct psb_intel_sdvo *sdvo = adapter->algo_data;
	return sdvo->i2c->algo->functionality(sdvo->i2c);
}