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
struct adapter_info {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct adapter_info const*) ; 
 struct adapter_info const* t3_adap_info ; 

const struct adapter_info *t3_get_adapter_info(unsigned int id)
{
	return id < ARRAY_SIZE(t3_adap_info) ? &t3_adap_info[id] : NULL;
}