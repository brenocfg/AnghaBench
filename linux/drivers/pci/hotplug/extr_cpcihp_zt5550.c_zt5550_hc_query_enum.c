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

/* Variables and functions */
 int ENUM_MASK ; 
 int /*<<< orphan*/  ENUM_PORT ; 
 int inb_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zt5550_hc_query_enum(void)
{
	u8 value;

	value = inb_p(ENUM_PORT);
	return ((value & ENUM_MASK) == ENUM_MASK);
}