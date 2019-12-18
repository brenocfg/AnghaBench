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
struct siox_master {int dummy; } ;

/* Variables and functions */
 int __siox_start (struct siox_master*) ; 
 int /*<<< orphan*/  siox_master_lock (struct siox_master*) ; 
 int /*<<< orphan*/  siox_master_unlock (struct siox_master*) ; 

__attribute__((used)) static int siox_start(struct siox_master *smaster)
{
	int ret;

	siox_master_lock(smaster);
	ret = __siox_start(smaster);
	siox_master_unlock(smaster);

	return ret;
}