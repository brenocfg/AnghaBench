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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int DRXDAP_FASI_ADDR2BANK (int /*<<< orphan*/ ) ; 
 int DRXDAP_FASI_ADDR2BLOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
bool is_handled_by_aud_tr_if(u32 addr)
{
	bool retval = false;

	if ((DRXDAP_FASI_ADDR2BLOCK(addr) == 4) &&
	    (DRXDAP_FASI_ADDR2BANK(addr) > 1) &&
	    (DRXDAP_FASI_ADDR2BANK(addr) < 6)) {
		retval = true;
	}

	return retval;
}