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
typedef  int u32 ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_TYPE ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT ; 

__attribute__((used)) static inline u32 nfp_flower_cmsg_phys_port(u8 phys_port)
{
	return FIELD_PREP(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM, phys_port) |
		FIELD_PREP(NFP_FLOWER_CMSG_PORT_TYPE,
			   NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT);
}