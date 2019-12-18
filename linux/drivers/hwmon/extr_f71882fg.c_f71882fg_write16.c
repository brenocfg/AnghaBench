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
typedef  int u16 ;
struct f71882fg_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  f71882fg_write8 (struct f71882fg_data*,scalar_t__,int) ; 

__attribute__((used)) static void f71882fg_write16(struct f71882fg_data *data, u8 reg, u16 val)
{
	f71882fg_write8(data, reg,     val >> 8);
	f71882fg_write8(data, reg + 1, val & 0xff);
}