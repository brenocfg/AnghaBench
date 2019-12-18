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
typedef  int /*<<< orphan*/  u_char ;
struct sym_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  S24C16_set_bit (struct sym_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_BIT ; 
 int /*<<< orphan*/  SET_CLK ; 

__attribute__((used)) static void S24C16_stop(struct sym_device *np, u_char *gpreg)
{
	S24C16_set_bit(np, 0, gpreg, SET_CLK);
	S24C16_set_bit(np, 1, gpreg, SET_BIT);
}