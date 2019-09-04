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
struct be_res_desc_hdr {scalar_t__ desc_type; int desc_len; } ;
struct be_port_res_desc {int dummy; } ;

/* Variables and functions */
 scalar_t__ PORT_RESOURCE_DESC_TYPE_V1 ; 
 int RESOURCE_DESC_SIZE_V0 ; 

__attribute__((used)) static struct be_port_res_desc *be_get_port_desc(u8 *buf, u32 desc_count)
{
	struct be_res_desc_hdr *hdr = (struct be_res_desc_hdr *)buf;
	int i;

	for (i = 0; i < desc_count; i++) {
		if (hdr->desc_type == PORT_RESOURCE_DESC_TYPE_V1)
			return (struct be_port_res_desc *)hdr;

		hdr->desc_len = hdr->desc_len ? : RESOURCE_DESC_SIZE_V0;
		hdr = (void *)hdr + hdr->desc_len;
	}
	return NULL;
}