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
typedef  int u16 ;
struct channel_tlv {int type; int length; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void bnx2x_add_tlv(struct bnx2x *bp, void *tlvs_list,
			  u16 offset, u16 type, u16 length)
{
	struct channel_tlv *tl =
		(struct channel_tlv *)(tlvs_list + offset);

	tl->type = type;
	tl->length = length;
}