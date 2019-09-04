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
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pseudo_lock_minor_avail ; 

__attribute__((used)) static void pseudo_lock_minor_release(unsigned int minor)
{
	__set_bit(minor, &pseudo_lock_minor_avail);
}