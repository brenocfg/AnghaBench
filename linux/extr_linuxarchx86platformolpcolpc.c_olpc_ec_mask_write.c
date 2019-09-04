#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_WRITE_EXT_SCI_MASK ; 
 int /*<<< orphan*/  EC_WRITE_SCI_MASK ; 
 int OLPC_F_EC_WIDE_SCI ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ olpc_platform_info ; 

int olpc_ec_mask_write(u16 bits)
{
	if (olpc_platform_info.flags & OLPC_F_EC_WIDE_SCI) {
		__be16 ec_word = cpu_to_be16(bits);
		return olpc_ec_cmd(EC_WRITE_EXT_SCI_MASK, (void *) &ec_word, 2,
				   NULL, 0);
	} else {
		unsigned char ec_byte = bits & 0xff;
		return olpc_ec_cmd(EC_WRITE_SCI_MASK, &ec_byte, 1, NULL, 0);
	}
}