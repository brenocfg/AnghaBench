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
typedef  scalar_t__ u32 ;
struct vfe_format {scalar_t__ code; int /*<<< orphan*/  bpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static u8 vfe_get_bpp(const struct vfe_format *formats,
		      unsigned int nformats, u32 code)
{
	unsigned int i;

	for (i = 0; i < nformats; i++)
		if (code == formats[i].code)
			return formats[i].bpp;

	WARN(1, "Unknown format\n");

	return formats[0].bpp;
}