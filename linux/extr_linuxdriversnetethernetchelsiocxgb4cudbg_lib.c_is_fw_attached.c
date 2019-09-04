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
struct cudbg_init {struct adapter* adap; } ;
struct adapter {int flags; scalar_t__ use_bd; } ;

/* Variables and functions */
 int FW_OK ; 

__attribute__((used)) static int is_fw_attached(struct cudbg_init *pdbg_init)
{
	struct adapter *padap = pdbg_init->adap;

	if (!(padap->flags & FW_OK) || padap->use_bd)
		return 0;

	return 1;
}