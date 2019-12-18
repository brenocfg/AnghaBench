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
struct mei_msg_hdr {scalar_t__ host_addr; scalar_t__ me_addr; } ;

/* Variables and functions */

__attribute__((used)) static inline bool hdr_is_hbm(struct mei_msg_hdr *mei_hdr)
{
	return mei_hdr->host_addr == 0 && mei_hdr->me_addr == 0;
}