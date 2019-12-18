#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int id; char const* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* fw_capa_map ; 

__attribute__((used)) static const char *ath6kl_init_get_fw_capa_name(unsigned int id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fw_capa_map); i++) {
		if (fw_capa_map[i].id == id)
			return fw_capa_map[i].name;
	}

	return "<unknown>";
}