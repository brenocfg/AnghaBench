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
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  MLX5E_FTE_SET (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ip_protocol ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  udp_dport ; 
 int /*<<< orphan*/  udp_sport ; 

__attribute__((used)) static void
set_udp(void *headers_c, void *headers_v, __be16 psrc_m, __be16 psrc_v,
	__be16 pdst_m, __be16 pdst_v)
{
	if (psrc_m) {
		MLX5E_FTE_SET(headers_c, udp_sport, ntohs(psrc_m));
		MLX5E_FTE_SET(headers_v, udp_sport, ntohs(psrc_v));
	}

	if (pdst_m) {
		MLX5E_FTE_SET(headers_c, udp_dport, ntohs(pdst_m));
		MLX5E_FTE_SET(headers_v, udp_dport, ntohs(pdst_v));
	}

	MLX5E_FTE_SET(headers_c, ip_protocol, 0xffff);
	MLX5E_FTE_SET(headers_v, ip_protocol, IPPROTO_UDP);
}