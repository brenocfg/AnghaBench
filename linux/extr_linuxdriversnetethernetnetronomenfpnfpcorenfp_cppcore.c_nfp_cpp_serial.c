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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_cpp {int /*<<< orphan*/ * serial; } ;

/* Variables and functions */

int nfp_cpp_serial(struct nfp_cpp *cpp, const u8 **serial)
{
	*serial = &cpp->serial[0];
	return sizeof(cpp->serial);
}