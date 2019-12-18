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
typedef  int /*<<< orphan*/  u32 ;
struct vcap_data {int dummy; } ;
typedef  enum ocelot_vcap_bit { ____Placeholder_ocelot_vcap_bit } ocelot_vcap_bit ;

/* Variables and functions */
 int OCELOT_VCAP_BIT_1 ; 
 int OCELOT_VCAP_BIT_ANY ; 
 int /*<<< orphan*/  vcap_key_set (struct vcap_data*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void vcap_key_bit_set(struct vcap_data *data, u32 offset,
			     enum ocelot_vcap_bit val)
{
	vcap_key_set(data, offset, 1, val == OCELOT_VCAP_BIT_1 ? 1 : 0,
		     val == OCELOT_VCAP_BIT_ANY ? 0 : 1);
}