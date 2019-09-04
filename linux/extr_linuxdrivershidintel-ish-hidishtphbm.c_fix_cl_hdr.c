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
typedef  int /*<<< orphan*/  uint8_t ;
struct ishtp_msg_hdr {size_t length; int msg_complete; scalar_t__ reserved; int /*<<< orphan*/  fw_addr; scalar_t__ host_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline void fix_cl_hdr(struct ishtp_msg_hdr *hdr, size_t length,
	uint8_t cl_addr)
{
	hdr->host_addr = 0;
	hdr->fw_addr = cl_addr;
	hdr->length = length;
	hdr->msg_complete = 1;
	hdr->reserved = 0;
}