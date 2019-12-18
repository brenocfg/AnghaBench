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
struct rocker_tlv {int dummy; } ;
struct rocker_desc_info {TYPE_1__* desc; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tlv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  rocker_tlv_parse (struct rocker_tlv const**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
rocker_tlv_parse_desc(const struct rocker_tlv **tb, int maxtype,
		      const struct rocker_desc_info *desc_info)
{
	rocker_tlv_parse(tb, maxtype, desc_info->data,
			 desc_info->desc->tlv_size);
}