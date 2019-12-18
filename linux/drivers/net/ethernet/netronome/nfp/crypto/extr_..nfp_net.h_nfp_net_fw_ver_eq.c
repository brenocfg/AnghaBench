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
typedef  scalar_t__ u8 ;
struct nfp_net_fw_version {scalar_t__ resv; scalar_t__ class; scalar_t__ major; scalar_t__ minor; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfp_net_fw_ver_eq(struct nfp_net_fw_version *fw_ver,
				     u8 resv, u8 class, u8 major, u8 minor)
{
	return fw_ver->resv == resv &&
	       fw_ver->class == class &&
	       fw_ver->major == major &&
	       fw_ver->minor == minor;
}