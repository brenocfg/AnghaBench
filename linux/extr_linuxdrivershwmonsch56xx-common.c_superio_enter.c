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
 int EBUSY ; 
 int /*<<< orphan*/  SIO_UNLOCK_KEY ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  request_muxed_region (int,int,char*) ; 

__attribute__((used)) static inline int superio_enter(int base)
{
	/* Don't step on other drivers' I/O space by accident */
	if (!request_muxed_region(base, 2, "sch56xx")) {
		pr_err("I/O address 0x%04x already in use\n", base);
		return -EBUSY;
	}

	outb(SIO_UNLOCK_KEY, base);

	return 0;
}