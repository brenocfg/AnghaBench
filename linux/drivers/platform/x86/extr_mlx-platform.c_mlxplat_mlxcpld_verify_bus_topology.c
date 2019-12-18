#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_adapter {int dummy; } ;
struct TYPE_5__ {int shift_nr; } ;
struct TYPE_4__ {int parent; int base_nr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENODEV ; 
 int MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM ; 
 int MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR ; 
 struct i2c_adapter* i2c_get_adapter (int) ; 
 int /*<<< orphan*/  i2c_put_adapter (struct i2c_adapter*) ; 
 TYPE_2__* mlxplat_hotplug ; 
 TYPE_1__* mlxplat_mux_data ; 

__attribute__((used)) static int mlxplat_mlxcpld_verify_bus_topology(int *nr)
{
	struct i2c_adapter *search_adap;
	int shift, i;

	/* Scan adapters from expected id to verify it is free. */
	*nr = MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR;
	for (i = MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR; i <
	     MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM; i++) {
		search_adap = i2c_get_adapter(i);
		if (search_adap) {
			i2c_put_adapter(search_adap);
			continue;
		}

		/* Return if expected parent adapter is free. */
		if (i == MLXPLAT_CPLD_PHYS_ADAPTER_DEF_NR)
			return 0;
		break;
	}

	/* Return with error if free id for adapter is not found. */
	if (i == MLXPLAT_CPLD_MAX_PHYS_ADAPTER_NUM)
		return -ENODEV;

	/* Shift adapter ids, since expected parent adapter is not free. */
	*nr = i;
	for (i = 0; i < ARRAY_SIZE(mlxplat_mux_data); i++) {
		shift = *nr - mlxplat_mux_data[i].parent;
		mlxplat_mux_data[i].parent = *nr;
		mlxplat_mux_data[i].base_nr += shift;
		if (shift > 0)
			mlxplat_hotplug->shift_nr = shift;
	}

	return 0;
}