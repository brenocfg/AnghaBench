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
struct ks8995_switch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8995_REG_ID1 ; 
 int ks8995_write_reg (struct ks8995_switch*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ks8995_start(struct ks8995_switch *ks)
{
	return ks8995_write_reg(ks, KS8995_REG_ID1, 1);
}