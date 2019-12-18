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
typedef  size_t u32 ;
struct hsf_load_header {size_t* apps; } ;

/* Variables and functions */

__attribute__((used)) static inline u32
hsf_load_header_app_off(const struct hsf_load_header *hdr, u32 app)
{
	return hdr->apps[app];
}