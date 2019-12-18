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
struct timestamp_t {int hour; int min; int sec; int year; int mon; int day; } ;
struct dos_dentry_t {int /*<<< orphan*/  modify_date; int /*<<< orphan*/  modify_time; int /*<<< orphan*/  create_date; int /*<<< orphan*/  create_time; } ;
struct dentry_t {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET16_A (int /*<<< orphan*/ ,int) ; 
#define  TM_CREATE 129 
#define  TM_MODIFY 128 

void fat_set_entry_time(struct dentry_t *p_entry, struct timestamp_t *tp,
			u8 mode)
{
	u16 t, d;
	struct dos_dentry_t *ep = (struct dos_dentry_t *)p_entry;

	t = (tp->hour << 11) | (tp->min << 5) | (tp->sec >> 1);
	d = (tp->year <<  9) | (tp->mon << 5) |  tp->day;

	switch (mode) {
	case TM_CREATE:
		SET16_A(ep->create_time, t);
		SET16_A(ep->create_date, d);
		break;
	case TM_MODIFY:
		SET16_A(ep->modify_time, t);
		SET16_A(ep->modify_date, d);
		break;
	}
}