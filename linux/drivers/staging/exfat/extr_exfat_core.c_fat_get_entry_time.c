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
typedef  int u8 ;
typedef  int u16 ;
struct timestamp_t {int sec; int min; int hour; int day; int mon; int year; } ;
struct dos_dentry_t {int /*<<< orphan*/  modify_date; int /*<<< orphan*/  modify_time; int /*<<< orphan*/  create_date; int /*<<< orphan*/  create_time; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int GET16_A (int /*<<< orphan*/ ) ; 
#define  TM_CREATE 129 
#define  TM_MODIFY 128 

void fat_get_entry_time(struct dentry_t *p_entry, struct timestamp_t *tp,
			u8 mode)
{
	u16 t = 0x00, d = 0x21;
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	switch (mode) {
	case TM_CREATE:
		t = GET16_A(ep->create_time);
		d = GET16_A(ep->create_date);
		break;
	case TM_MODIFY:
		t = GET16_A(ep->modify_time);
		d = GET16_A(ep->modify_date);
		break;
	}

	tp->sec  = (t & 0x001F) << 1;
	tp->min  = (t >> 5) & 0x003F;
	tp->hour = (t >> 11);
	tp->day  = (d & 0x001F);
	tp->mon  = (d >> 5) & 0x000F;
	tp->year = (d >> 9);
}