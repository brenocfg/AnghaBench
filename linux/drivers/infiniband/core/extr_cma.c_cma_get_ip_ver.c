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
typedef  int u8 ;
struct cma_hdr {int ip_version; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 cma_get_ip_ver(const struct cma_hdr *hdr)
{
	return hdr->ip_version >> 4;
}