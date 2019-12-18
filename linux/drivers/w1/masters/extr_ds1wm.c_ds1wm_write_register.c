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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ds1wm_data {int bus_shift; int map; scalar_t__ is_hw_big_endian; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iowrite16be (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iowrite32 (int,int) ; 
 int /*<<< orphan*/  iowrite32be (int,int) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ds1wm_write_register(struct ds1wm_data *ds1wm_data, u32 reg,
					u8 val)
{
	if (ds1wm_data->is_hw_big_endian) {
		switch (ds1wm_data->bus_shift) {
		case 0:
			iowrite8(val, ds1wm_data->map + (reg << 0));
			break;
		case 1:
			iowrite16be((u16)val, ds1wm_data->map + (reg << 1));
			break;
		case 2:
			iowrite32be((u32)val, ds1wm_data->map + (reg << 2));
			break;
		}
	} else {
		switch (ds1wm_data->bus_shift) {
		case 0:
			iowrite8(val, ds1wm_data->map + (reg << 0));
			break;
		case 1:
			iowrite16((u16)val, ds1wm_data->map + (reg << 1));
			break;
		case 2:
			iowrite32((u32)val, ds1wm_data->map + (reg << 2));
			break;
		}
	}
}