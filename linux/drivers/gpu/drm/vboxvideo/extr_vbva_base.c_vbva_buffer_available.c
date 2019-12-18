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
typedef  scalar_t__ u32 ;
struct vbva_buffer {scalar_t__ data_offset; scalar_t__ free_offset; scalar_t__ data_len; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */

__attribute__((used)) static u32 vbva_buffer_available(const struct vbva_buffer *vbva)
{
	s32 diff = vbva->data_offset - vbva->free_offset;

	return diff > 0 ? diff : vbva->data_len + diff;
}