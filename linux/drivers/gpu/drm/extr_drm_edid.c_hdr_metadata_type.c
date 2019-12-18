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
typedef  int const uint8_t ;
typedef  int u8 ;

/* Variables and functions */
 int const BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_STATIC_METADATA_TYPE1 ; 

__attribute__((used)) static uint8_t hdr_metadata_type(const u8 *edid_ext)
{
	return edid_ext[3] &
		BIT(HDMI_STATIC_METADATA_TYPE1);
}