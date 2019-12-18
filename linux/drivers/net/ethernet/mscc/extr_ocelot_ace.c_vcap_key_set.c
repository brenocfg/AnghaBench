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
typedef  scalar_t__ u32 ;
struct vcap_data {scalar_t__ key_offset; int /*<<< orphan*/  mask; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  vcap_data_set (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void vcap_key_set(struct vcap_data *data, u32 offset, u32 width,
			 u32 value, u32 mask)
{
	vcap_data_set(data->entry, offset + data->key_offset, width, value);
	vcap_data_set(data->mask, offset + data->key_offset, width, mask);
}