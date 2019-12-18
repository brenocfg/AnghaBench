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
struct fcpio_tag {int dummy; } ;
struct fcpio_header {struct fcpio_tag tag; int /*<<< orphan*/  status; int /*<<< orphan*/  type; } ;

/* Variables and functions */

__attribute__((used)) static inline void
fcpio_header_dec(struct fcpio_header *hdr,
		 u8 *type, u8 *status,
		 struct fcpio_tag *tag)
{
	*type = hdr->type;
	*status = hdr->status;
	*tag = hdr->tag;
}