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
 int /*<<< orphan*/  io_mutex ; 
 unsigned int mec_emi_base ; 
 unsigned int mec_emi_end ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void cros_ec_lpc_mec_init(unsigned int base, unsigned int end)
{
	mutex_init(&io_mutex);
	mec_emi_base = base;
	mec_emi_end = end;
}