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
struct qib_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scl_out (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  sda_out (struct qib_devdata*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void start_seq(struct qib_devdata *dd)
{
	sda_out(dd, 1);
	scl_out(dd, 1);
	sda_out(dd, 0);
	udelay(1);
	scl_out(dd, 0);
}