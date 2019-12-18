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
typedef  int u32 ;
struct TYPE_2__ {int message_size; } ;
struct i2o_message {TYPE_1__ header; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 incoming_data_size(struct i2o_message *i2o_message)
{
	return (sizeof(u32) * i2o_message->header.message_size);
}