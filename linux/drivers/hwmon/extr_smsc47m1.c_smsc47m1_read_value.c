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
typedef  scalar_t__ u8 ;
struct smsc47m1_data {scalar_t__ addr; } ;

/* Variables and functions */
 int inb_p (scalar_t__) ; 

__attribute__((used)) static inline int smsc47m1_read_value(struct smsc47m1_data *data, u8 reg)
{
	return inb_p(data->addr + reg);
}