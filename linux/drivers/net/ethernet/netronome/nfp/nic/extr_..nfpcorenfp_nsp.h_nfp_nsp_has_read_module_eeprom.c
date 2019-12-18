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
struct nfp_nsp {int dummy; } ;

/* Variables and functions */
 int nfp_nsp_get_abi_ver_minor (struct nfp_nsp*) ; 

__attribute__((used)) static inline bool nfp_nsp_has_read_module_eeprom(struct nfp_nsp *state)
{
	return nfp_nsp_get_abi_ver_minor(state) > 28;
}