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
typedef  unsigned char u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_EXT_SCI_QUERY ; 
 int /*<<< orphan*/  EC_SCI_QUERY ; 
 int OLPC_F_EC_WIDE_SCI ; 
 unsigned char be16_to_cpu (int /*<<< orphan*/ ) ; 
 int olpc_ec_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char*,int) ; 
 TYPE_1__ olpc_platform_info ; 

int olpc_ec_sci_query(u16 *sci_value)
{
	int ret;

	if (olpc_platform_info.flags & OLPC_F_EC_WIDE_SCI) {
		__be16 ec_word;
		ret = olpc_ec_cmd(EC_EXT_SCI_QUERY,
			NULL, 0, (void *) &ec_word, 2);
		if (ret == 0)
			*sci_value = be16_to_cpu(ec_word);
	} else {
		unsigned char ec_byte;
		ret = olpc_ec_cmd(EC_SCI_QUERY, NULL, 0, &ec_byte, 1);
		if (ret == 0)
			*sci_value = ec_byte;
	}

	return ret;
}