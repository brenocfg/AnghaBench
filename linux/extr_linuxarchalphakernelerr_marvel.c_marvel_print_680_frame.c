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
struct ev7_lf_subpackets {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
marvel_print_680_frame(struct ev7_lf_subpackets *lf_subpackets)
{
#ifdef CONFIG_VERBOSE_MCHECK
	struct ev7_pal_environmental_subpacket *env;
	struct { int type; char *name; } ev_packets[] = {
		{ EL_TYPE__PAL__ENV__AMBIENT_TEMPERATURE,
		  "Ambient Temperature" },
		{ EL_TYPE__PAL__ENV__AIRMOVER_FAN,
		  "AirMover / Fan" },
		{ EL_TYPE__PAL__ENV__VOLTAGE,
		  "Voltage" },
		{ EL_TYPE__PAL__ENV__INTRUSION,
		  "Intrusion" },
		{ EL_TYPE__PAL__ENV__POWER_SUPPLY,
		  "Power Supply" },
		{ EL_TYPE__PAL__ENV__LAN,
		  "LAN" },
		{ EL_TYPE__PAL__ENV__HOT_PLUG,
		  "Hot Plug" },
		{ 0, NULL }
	};
	int i;

	for (i = 0; ev_packets[i].type != 0; i++) {
		env = lf_subpackets->env[ev7_lf_env_index(ev_packets[i].type)];
		if (!env)
			continue;

		printk("%s**%s event (cabinet %d, drawer %d)\n",
		       err_print_prefix,
		       ev_packets[i].name,
		       env->cabinet,
		       env->drawer);
		printk("%s   Module Type: 0x%x - Unit ID 0x%x - "
		       "Condition 0x%x\n",
		       err_print_prefix,
		       env->module_type,
		       env->unit_id,
		       env->condition);
	}
#endif /* CONFIG_VERBOSE_MCHECK */
}