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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  attr_mod; } ;
struct opa_vnic_vema_mad {TYPE_1__ mad_hdr; } ;

/* Variables and functions */
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 vema_get_vport_num(struct opa_vnic_vema_mad *recvd_mad)
{
	return be32_to_cpu(recvd_mad->mad_hdr.attr_mod) & 0xff;
}