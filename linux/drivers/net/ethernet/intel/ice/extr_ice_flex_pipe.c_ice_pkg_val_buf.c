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
typedef  scalar_t__ u16 ;
struct ice_buf_hdr {int /*<<< orphan*/  data_end; int /*<<< orphan*/  section_count; } ;
struct ice_buf {scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ ICE_MAX_S_COUNT ; 
 scalar_t__ ICE_MAX_S_DATA_END ; 
 scalar_t__ ICE_MIN_S_COUNT ; 
 scalar_t__ ICE_MIN_S_DATA_END ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ice_buf_hdr *ice_pkg_val_buf(struct ice_buf *buf)
{
	struct ice_buf_hdr *hdr;
	u16 section_count;
	u16 data_end;

	hdr = (struct ice_buf_hdr *)buf->buf;
	/* verify data */
	section_count = le16_to_cpu(hdr->section_count);
	if (section_count < ICE_MIN_S_COUNT || section_count > ICE_MAX_S_COUNT)
		return NULL;

	data_end = le16_to_cpu(hdr->data_end);
	if (data_end < ICE_MIN_S_DATA_END || data_end > ICE_MAX_S_DATA_END)
		return NULL;

	return hdr;
}