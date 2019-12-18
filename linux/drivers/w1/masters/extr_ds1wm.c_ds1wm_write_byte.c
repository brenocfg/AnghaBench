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
typedef  int /*<<< orphan*/  u8 ;
struct ds1wm_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds1wm_write (struct ds1wm_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ds1wm_write_byte(void *data, u8 byte)
{
	struct ds1wm_data *ds1wm_data = data;

	ds1wm_write(ds1wm_data, byte);
}