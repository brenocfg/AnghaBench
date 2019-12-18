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
struct rocker_tlv {int dummy; } ;
struct rocker_desc_info {char const* tlv_size; int data; } ;

/* Variables and functions */

__attribute__((used)) static inline void rocker_tlv_nest_cancel(struct rocker_desc_info *desc_info,
					  const struct rocker_tlv *start)
{
	desc_info->tlv_size = (const char *) start - desc_info->data;
}