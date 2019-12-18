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
struct power_per_rate {scalar_t__ bw20; scalar_t__ bw40; int /*<<< orphan*/  raw; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 scalar_t__ s6_to_int (int) ; 
 int /*<<< orphan*/  s6_validate (int) ; 

__attribute__((used)) static void
mt7601u_set_power_rate(struct power_per_rate *rate, s8 delta, u8 value)
{
	/* Invalid? Note: vendor driver does not handle this */
	if (value == 0xff)
		return;

	rate->raw = s6_validate(value);
	rate->bw20 = s6_to_int(value);
	/* Note: vendor driver does cap the value to s6 right away */
	rate->bw40 = rate->bw20 + delta;
}