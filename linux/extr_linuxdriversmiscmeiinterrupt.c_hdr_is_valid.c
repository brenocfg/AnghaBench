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
typedef  int /*<<< orphan*/  u32 ;
struct mei_msg_hdr {scalar_t__ reserved; } ;

/* Variables and functions */
 int EBADMSG ; 

__attribute__((used)) static inline int hdr_is_valid(u32 msg_hdr)
{
	struct mei_msg_hdr *mei_hdr;

	mei_hdr = (struct mei_msg_hdr *)&msg_hdr;
	if (!msg_hdr || mei_hdr->reserved)
		return -EBADMSG;

	return 0;
}