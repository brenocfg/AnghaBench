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

/* Variables and functions */
 scalar_t__ A20_TEST_ADDR ; 
 int /*<<< orphan*/  io_delay () ; 
 int rdfs32 (scalar_t__) ; 
 int rdgs32 (scalar_t__) ; 
 int /*<<< orphan*/  set_fs (int) ; 
 int /*<<< orphan*/  set_gs (int) ; 
 int /*<<< orphan*/  wrfs32 (int,scalar_t__) ; 

__attribute__((used)) static int a20_test(int loops)
{
	int ok = 0;
	int saved, ctr;

	set_fs(0x0000);
	set_gs(0xffff);

	saved = ctr = rdfs32(A20_TEST_ADDR);

	while (loops--) {
		wrfs32(++ctr, A20_TEST_ADDR);
		io_delay();	/* Serialize and make delay constant */
		ok = rdgs32(A20_TEST_ADDR+0x10) ^ ctr;
		if (ok)
			break;
	}

	wrfs32(saved, A20_TEST_ADDR);
	return ok;
}