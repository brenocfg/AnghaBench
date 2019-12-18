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
typedef  int u32 ;
struct zd_ioreq16 {int member_1; int /*<<< orphan*/  member_0; } ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq16 const*) ; 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZD_CR242 ; 
 int /*<<< orphan*/  ZD_CR243 ; 
 int /*<<< orphan*/  ZD_CR244 ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_iowrite16a_locked (struct zd_chip*,struct zd_ioreq16 const*,int /*<<< orphan*/ ) ; 

int zd_rfwrite_cr_locked(struct zd_chip *chip, u32 value)
{
	const struct zd_ioreq16 ioreqs[] = {
		{ ZD_CR244, (value >> 16) & 0xff },
		{ ZD_CR243, (value >>  8) & 0xff },
		{ ZD_CR242,  value        & 0xff },
	};
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	return zd_iowrite16a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
}